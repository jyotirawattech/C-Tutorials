#!/usr/bin/env python3
"""Check exported accepted-source integrity; optionally compile without executing it."""
from __future__ import annotations

import argparse
from datetime import date, datetime
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
from urllib.parse import urlsplit

OWNER = "https://leetcode.com/u/user0592I/"
MAX_JSON_BYTES = 2_000_000
MAX_SOURCE_BYTES = 1_000_000
# Explicit environment types for this observed archive, not guessed from identifiers.
TYPE_FLAGS = {
    83: ["LC_LIST_NODE"], 106: ["LC_TREE_NODE"], 138: ["LC_RANDOM_NODE"],
    141: ["LC_LIST_NODE"], 147: ["LC_LIST_NODE"], 206: ["LC_LIST_NODE"],
    328: ["LC_LIST_NODE"],
}
STANDARD_HEADERS = {
    "assert.h", "ctype.h", "errno.h", "float.h", "inttypes.h", "limits.h",
    "math.h", "stdbool.h", "stddef.h", "stdint.h", "stdio.h", "stdlib.h",
    "string.h", "time.h", "wchar.h", "wctype.h", "complex.h",
}
DANGEROUS_CALLS = re.compile(
    r"\b(?:system|popen|pclose|exec[a-z]*|fork|vfork|posix_spawn[a-z]*|"
    r"socket|connect|bind|listen|accept|send|recv|dlopen|dlsym|"
    r"fopen|freopen|open|openat|creat|read|write|unlink|remove|rename|"
    r"rmdir|chmod|chown|setuid|setgid|kill)\s*\("
)
COMMENTS_AND_LITERALS = re.compile(
    r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\x27(?:\\.|[^\x27\\])*\x27',
    re.S,
)
COMMENTS = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)


def load_json(path: Path):
    if path.is_symlink() or path.stat().st_size > MAX_JSON_BYTES:
        raise ValueError("symlink or oversized JSON")
    return json.loads(path.read_text(encoding="utf-8"))


def safe_file(root: Path, relative: str) -> Path:
    if not isinstance(relative, str) or not relative or "\\" in relative:
        raise ValueError("invalid archive path")
    path = Path(relative)
    if path.is_absolute() or ".." in path.parts:
        raise ValueError("archive path escapes repository")
    full = root / path
    if any(p.is_symlink() for p in [full, *full.parents] if p != root.parent):
        raise ValueError("symlink in archive path")
    full.resolve().relative_to(root.resolve())
    return full


def canonical_owner(value) -> bool:
    return isinstance(value, str) and value.rstrip("/") == OWNER.rstrip("/")


def leetcode_url(value, prefix: str) -> bool:
    if not isinstance(value, str):
        return False
    parsed = urlsplit(value)
    return (parsed.scheme == "https" and parsed.netloc == "leetcode.com"
            and not parsed.query and not parsed.fragment
            and parsed.path.startswith(prefix))


def scan_source(code: str) -> list[str]:
    """Conservative review gate, not a complete security proof of arbitrary C."""
    issues = []
    logical = code.replace("\\\r\n", "").replace("\\\n", "")
    without_comments = COMMENTS.sub("", logical)
    for line in without_comments.splitlines():
        directive = re.match(r"^\s*#\s*(\w+)\s*(.*)", line)
        if not directive:
            continue
        name, argument = directive.groups()
        if name == "include":
            include = re.fullmatch(r'[<"]([^>"]+)[>"]\s*', argument)
            if include is None:
                issues.append("dynamic or malformed include")
            elif include.group(1) == "uthash.h":
                issues.append("unsupported dependency: uthash.h (not vendored)")
            elif include.group(1) not in STANDARD_HEADERS:
                issues.append("unapproved include: " + include.group(1))
        elif name not in {"define", "undef", "if", "ifdef", "ifndef", "elif", "else", "endif"}:
            issues.append("unapproved preprocessor directive: " + name)
    tokens = COMMENTS_AND_LITERALS.sub(" ", logical)
    if DANGEROUS_CALLS.search(tokens):
        issues.append("process, network, dynamic-loader or filesystem call")
    if re.search(r"\b(?:__asm__|__asm|asm)\b|__attribute__\s*\(\(\s*(?:constructor|destructor)", tokens):
        issues.append("assembly or load-time execution attribute")
    if "UT_hash_handle" in tokens and not any("uthash.h" in i for i in issues):
        issues.append("unsupported dependency: uthash.h (implicit platform header)")
    return sorted(set(issues))


def validate_archive(root: Path, expected_count: int = 83, raw_dir: Path | None = None):
    errors, records = [], []
    root = root.resolve()
    try:
        index = load_json(root / "leetcode/accepted/index.json")
    except (OSError, ValueError, TypeError) as exc:
        return {"integrity_passed": False, "errors": ["index: " + str(exc)], "entries": []}
    if not isinstance(index, dict):
        return {"integrity_passed": False, "errors": ["index must be an object"], "entries": []}
    entries = index.get("entries")
    if not isinstance(entries, list):
        return {"integrity_passed": False, "errors": ["index entries must be an array"], "entries": []}
    if index.get("expected_count") != expected_count or len(entries) != expected_count:
        errors.append(f"coverage: expected {expected_count}, observed {len(entries)}")
    if not canonical_owner(index.get("owner_profile_url")):
        errors.append("index owner mismatch")
    seen_ids, seen_paths, seen_submissions = set(), set(), set()
    for item in entries:
        label = str(item.get("problem_id", "invalid")) if isinstance(item, dict) else "invalid"
        try:
            if not isinstance(item, dict):
                raise ValueError("index entry must be an object")
            problem_id, slug, relative = item["problem_id"], item["slug"], item["path"]
            if type(problem_id) is not int or problem_id < 1:
                raise ValueError("invalid problem ID")
            if not isinstance(slug, str) or not re.fullmatch(r"[a-z0-9]+(?:-[a-z0-9]+)*", slug):
                raise ValueError("invalid slug")
            expected_path = f"leetcode/accepted/{problem_id:04d}_{slug.replace('-', '_')}"
            if relative != expected_path:
                raise ValueError("entry path does not match problem ID and slug")
            if problem_id in seen_ids or relative in seen_paths:
                raise ValueError("duplicate problem ID or path")
            seen_ids.add(problem_id)
            seen_paths.add(relative)
            folder = safe_file(root, relative)
            metadata = load_json(folder / "metadata.json")
            if not isinstance(metadata, dict):
                raise ValueError("metadata must be an object")
            source_path = safe_file(root, relative + "/submission.c")
            if source_path.stat().st_size > MAX_SOURCE_BYTES:
                raise ValueError("oversized source")
            source = source_path.read_bytes()
            code = source.decode("utf-8")
            if not code.strip():
                raise ValueError("empty source")
            if metadata.get("problem_id") != problem_id or metadata.get("slug") != slug:
                raise ValueError("metadata problem identity mismatch")
            if not isinstance(metadata.get("title"), str) or not metadata["title"].strip():
                raise ValueError("missing title")
            if metadata.get("verdict") != "Accepted" or metadata.get("language") != "C":
                raise ValueError("entry is not a captured Accepted C submission")
            if not canonical_owner(metadata.get("owner_profile_url")):
                raise ValueError("entry owner mismatch")
            if metadata.get("problem_url") != f"https://leetcode.com/problems/{slug}/":
                raise ValueError("problem URL mismatch")
            submission_url = metadata.get("submission_url")
            if (not leetcode_url(submission_url, "/submissions/detail/")
                    or not re.fullmatch(r"/submissions/detail/[0-9]+/", urlsplit(submission_url).path)):
                raise ValueError("invalid submission URL")
            if submission_url in seen_submissions:
                raise ValueError("duplicate submission receipt")
            seen_submissions.add(submission_url)
            digest = hashlib.sha256(source).hexdigest()
            if metadata.get("source_sha256") != digest:
                raise ValueError("exported source hash mismatch")
            displayed_time = metadata.get("displayed_submission_time")
            if not isinstance(displayed_time, str) or not displayed_time.strip():
                raise ValueError("missing displayed submission time")
            if str(metadata.get("displayed_timezone")).lower() != "unspecified":
                raise ValueError("displayed timezone must remain Unspecified")
            if metadata.get("original_practice_date") != "Unknown" or metadata.get("original_assistance") != "Unknown":
                raise ValueError("unverified original practice date/assistance must remain Unknown")
            datetime.fromisoformat(metadata["captured_at"].replace("Z", "+00:00"))
            date.fromisoformat(metadata["publication_date"])
            notes = safe_file(root, relative + "/README.md").read_text(encoding="utf-8")
            if metadata["problem_url"] not in notes or submission_url not in notes:
                raise ValueError("README lacks exact problem/submission links")
            if raw_dir is not None:
                padded = raw_dir / f"{problem_id:04d}.json"
                raw = load_json(padded if padded.exists() else raw_dir / f"{problem_id}.json")
                if (raw.get("id") != problem_id or raw.get("slug") != slug
                        or raw.get("title") != metadata["title"]
                        or raw.get("submission_url") != submission_url
                        or raw.get("problem_url") != metadata["problem_url"]):
                    raise ValueError("private capture identity mismatch")
                if raw.get("code", "").encode("utf-8") != source:
                    raise ValueError("private visible-source export bytes mismatch")
                if not canonical_owner(raw.get("owner_url")) or raw.get("language_class") != "language-c":
                    raise ValueError("private capture owner/language mismatch")
                if not re.search(r"(?:^|\n)Accepted(?:\n|$)", raw.get("prelude", "")):
                    raise ValueError("private capture does not show Accepted")
                timestamp = re.search(r"submitted at\s+([^\n]+)", raw.get("prelude", ""))
                if timestamp is None or " ".join(timestamp[1].split()) != " ".join(displayed_time.split()):
                    raise ValueError("private capture displayed time mismatch")
                if metadata["captured_at"] != raw.get("observed_at"):
                    raise ValueError("private capture observation time mismatch")
            records.append({"problem_id": problem_id, "path": relative, "source_sha256": digest,
                            "source_review": scan_source(code)})
        except (OSError, ValueError, TypeError, KeyError, UnicodeError) as exc:
            errors.append(label + ": " + str(exc))
    actual_dirs = {p.relative_to(root).as_posix()
                   for p in (root / "leetcode/accepted").iterdir() if p.is_dir()}
    if actual_dirs != seen_paths:
        errors.append("entry directory/index coverage mismatch")
    return {"integrity_passed": not errors, "expected_count": expected_count,
            "validated_entries": len(records), "private_capture_comparison": raw_dir is not None,
            "errors": errors, "entries": records}


def compile_entry(root: Path, entry: dict, compiler: str) -> dict:
    """Compile one translation unit to an object; never link or execute source."""
    result = {"problem_id": entry["problem_id"], "status": "not_compiled"}
    issues = entry["source_review"]
    if issues:
        result.update(status="blocked_source_review", reasons=issues)
        return result
    source = root / entry["path"] / "submission.c"
    header = root / "scripts/leetcode_compat.h"
    with tempfile.TemporaryDirectory(prefix="leetcode-compile-") as build:
        command = [compiler, "-std=c11", "-Wall", "-Wextra", "-Wpedantic",
                   "-include", str(header)]
        command.extend("-D" + name for name in TYPE_FLAGS.get(entry["problem_id"], []))
        command.extend(["-c", str(source), "-o", str(Path(build) / "submission.o")])
        try:
            completed = subprocess.run(command, capture_output=True, text=True,
                                       timeout=30, check=False)
            result.update(status="compiled" if completed.returncode == 0 else "compile_failed",
                          returncode=completed.returncode,
                          diagnostics=completed.stderr[:12000])
        except (OSError, subprocess.TimeoutExpired) as exc:
            result.update(status="compiler_unavailable_or_timeout", diagnostics=str(exc))
    return result


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    parser.add_argument("--expected-count", type=int, default=83)
    parser.add_argument("--raw-dir", type=Path, help="Optional private visible-source exports; never uploaded")
    parser.add_argument("--compile", action="store_true", help="Review then compile only; never execute archives")
    parser.add_argument("--cc", default="clang", help="One compiler executable, not a shell command")
    args = parser.parse_args()
    root = args.root.resolve()
    result = validate_archive(root, args.expected_count, args.raw_dir)
    if args.compile and result["integrity_passed"]:
        compiler = shutil.which(args.cc)
        if compiler is None:
            result["compilation"] = {"error": "compiler unavailable"}
            print(json.dumps(result, indent=2))
            return 2
        compiled = [compile_entry(root, item, compiler) for item in result["entries"]]
        result["compilation"] = {
            "mode": "object compilation only; no source execution or behavioral claim",
            "compiled": sum(item["status"] == "compiled" for item in compiled),
            "total": len(compiled), "results": compiled,
        }
    print(json.dumps(result, indent=2))
    if not result["integrity_passed"]:
        return 1
    if args.compile and any(item["status"] != "compiled" for item in result["compilation"]["results"]):
        return 2
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
