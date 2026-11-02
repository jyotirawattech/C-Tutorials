#!/usr/bin/env python3
"""Validate comparison provenance and reject unsupported measured-gain claims."""
from __future__ import annotations

import argparse
from datetime import datetime
from decimal import Decimal
import hashlib
import json
from pathlib import Path
import re

import check_accepted as accepted

VERDICTS = {"advantage_with_conditions", "same_or_worse",
            "not_established", "known_correctness_limit"}
NUMBER = re.compile(r"(?:0|[1-9][0-9]*)(?:\.[0-9]+)?")
PERCENT = re.compile(r"(?:0|[1-9][0-9]*)(?:\.[0-9]+)?%")
UI_METRICS = re.compile(
    r"Runtime\s*([0-9]+(?:\.[0-9]+)?)\s*ms\s*Beats\s*"
    r"([0-9]+(?:\.[0-9]+)?%)\s*Memory\s*"
    r"([0-9]+(?:\.[0-9]+)?)\s*MB\s*Beats\s*([0-9]+(?:\.[0-9]+)?%)"
)
UNSUPPORTED_GAINS = [
    re.compile(r"\b[0-9]+(?:\.[0-9]+)?\s*%\s*(?:faster|slower|less memory)\b", re.I),
    re.compile(r"\b[0-9]+(?:\.[0-9]+)?\s*(?:x|×|times)\s*(?:faster|speedup|less memory)\b", re.I),
    re.compile(r"\b(?:measured\s+)?speedup(?:_factor| factor)?\s*[:=]\s*[0-9]", re.I),
    re.compile(r"\b0(?:\.0+)?\s*ms\s*(?:means|proves|is|=)\s*(?:instant|zero execution|infinit)", re.I),
    re.compile(r"\b[0-9]+(?:\.[0-9]+)?\s*/\s*0(?:\.0+)?(?:\s*ms)?\s*(?:=|gives|yields|implies)", re.I),
]


def required_string(value, label):
    if not isinstance(value, str) or not value.strip() or len(value) > 8000:
        raise ValueError("missing or invalid " + label)
    return value


def check_numeric_display(value, label):
    if not isinstance(value, str) or not NUMBER.fullmatch(value):
        raise ValueError("invalid numeric UI display: " + label)


def check_percentile(value, label):
    if not isinstance(value, str) or not PERCENT.fullmatch(value):
        raise ValueError("invalid percentile display: " + label)
    if not Decimal(0) <= Decimal(value[:-1]) <= Decimal(100):
        raise ValueError("percentile outside 0..100: " + label)


def check_claims(text):
    # These are obvious text/schema guards, not a proof of complexity or correctness.
    for rule in UNSUPPORTED_GAINS:
        if rule.search(text):
            raise ValueError("unsupported measured gain, percentile-as-speed, or zero-runtime division claim")


def validate_comparison(comparison, metadata, raw=None):
    if not isinstance(comparison, dict):
        raise ValueError("comparison must be an object")
    for key in ["problem_id", "source_sha256"]:
        if comparison.get(key) != metadata.get(key):
            raise ValueError("metadata mismatch: " + key)
    if type(comparison["problem_id"]) is not int:
        raise ValueError("invalid comparison problem ID type")
    source_url = metadata["submission_url"]
    if comparison.get("source_submission_url") != source_url:
        raise ValueError("metadata mismatch: source_submission_url")
    for section, fields in [("baseline", ["name", "approach", "time", "space"]),
                            ("archived", ["name", "time", "space"])]:
        item = comparison.get(section)
        if not isinstance(item, dict):
            raise ValueError("missing " + section)
        for field in fields:
            required_string(item.get(field), section + "." + field)
    prose = []
    for field in ["why", "quantitative_comparison", "tradeoffs", "evidence_basis"]:
        prose.append(required_string(comparison.get(field), field))
    if comparison.get("verdict") not in VERDICTS:
        raise ValueError("invalid verdict")
    for section in ["baseline", "archived"]:
        prose.extend(comparison[section].values())
    check_claims(" ".join(str(text) for text in prose))
    paired = comparison.get("paired_benchmark")
    if (not isinstance(paired, dict)
            or set(paired) != {"status", "speedup_factor", "memory_reduction_percent"}
            or paired.get("status") != "not_run"
            or "speedup_factor" not in paired or paired["speedup_factor"] is not None
            or "memory_reduction_percent" not in paired or paired["memory_reduction_percent"] is not None):
        raise ValueError("paired benchmark not run: measured gain fields must be null")
    snapshot = comparison.get("judge_snapshot")
    if not isinstance(snapshot, dict):
        raise ValueError("missing judge_snapshot")
    if set(snapshot) != {"runtime_display", "runtime_unit", "runtime_beats_display",
                         "memory_display", "memory_unit", "memory_beats_display",
                         "captured_at", "source_submission_url"}:
        raise ValueError("judge snapshot fields do not match the captured UI schema")
    for field in ["runtime_display", "memory_display"]:
        check_numeric_display(snapshot.get(field), field)
    for field in ["runtime_beats_display", "memory_beats_display"]:
        check_percentile(snapshot.get(field), field)
    if snapshot.get("runtime_unit") != "ms" or snapshot.get("memory_unit") != "MB":
        raise ValueError("invalid UI metric units")
    if snapshot.get("source_submission_url") != source_url:
        raise ValueError("judge snapshot source mismatch")
    captured = required_string(snapshot.get("captured_at"), "judge_snapshot.captured_at")
    when = datetime.fromisoformat(captured.replace("Z", "+00:00"))
    if when.tzinfo is None:
        raise ValueError("judge snapshot capture requires timezone")
    if raw is not None:
        if not isinstance(raw, dict) or not isinstance(raw.get("code"), str):
            raise ValueError("private snapshot must contain a captured source string")
        if (raw.get("submission_url") != source_url
                or raw.get("id") != metadata["problem_id"]
                or not accepted.canonical_owner(raw.get("owner_url"))
                or raw.get("language_class") != "language-c"
                or not re.search(r"(?:^|\n)Accepted(?:\n|$)", raw.get("prelude", ""))):
            raise ValueError("private snapshot identity/owner/verdict mismatch")
        if hashlib.sha256(raw.get("code", "").encode("utf-8")).hexdigest() != metadata["source_sha256"]:
            raise ValueError("private snapshot source hash mismatch")
        match = UI_METRICS.search(raw.get("prelude", ""))
        if match is None:
            raise ValueError("private snapshot metric fields missing")
        expected = dict(zip(
            ["runtime_display", "runtime_beats_display", "memory_display", "memory_beats_display"],
            match.groups()))
        if any(snapshot[field] != value for field, value in expected.items()):
            raise ValueError("private snapshot exact display mismatch")
        if captured != raw.get("observed_at"):
            raise ValueError("private snapshot capture time mismatch")
    return {"problem_id": metadata["problem_id"], "verdict": comparison["verdict"],
            "source_sha256": metadata["source_sha256"],
            "judge_snapshot_captured_at": captured, "paired_benchmark": "not_run"}


def validate_comparisons(root: Path, expected_count=83, raw_dir=None):
    root = root.resolve()
    source = accepted.validate_archive(root, expected_count=expected_count)
    errors, records = list(source["errors"]), []
    if not source["integrity_passed"]:
        return {"comparison_evidence_passed": False, "errors": errors,
                "validated_comparisons": 0, "expected_count": expected_count, "entries": []}
    for entry in source["entries"]:
        try:
            folder = accepted.safe_file(root, entry["path"])
            metadata = accepted.load_json(folder / "metadata.json")
            comparison = accepted.load_json(folder / "comparison.json")
            raw = None
            if raw_dir is not None:
                padded = raw_dir / f'{metadata["problem_id"]:04d}.json'
                raw = accepted.load_json(
                    padded if padded.exists() else raw_dir / f'{metadata["problem_id"]}.json')
            records.append(validate_comparison(comparison, metadata, raw))
        except (OSError, ValueError, TypeError, KeyError) as exc:
            errors.append(str(entry["problem_id"]) + ": " + str(exc))
    if len(records) != expected_count:
        errors.append(f"comparison coverage: expected {expected_count}, observed {len(records)}")
    return {"comparison_evidence_passed": not errors, "expected_count": expected_count,
            "validated_comparisons": len(records), "private_ui_comparison": raw_dir is not None,
            "errors": errors, "entries": records,
            "limits": "Schema, source identity and obvious false-claim guards only; theoretical bounds and prose require human review. No paired benchmark was run."}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    parser.add_argument("--expected-count", type=int, default=83)
    parser.add_argument("--raw-dir", type=Path, help="Private UI captures; never uploaded")
    args = parser.parse_args()
    result = validate_comparisons(args.root, args.expected_count, args.raw_dir)
    print(json.dumps(result, indent=2))
    return 0 if result["comparison_evidence_passed"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
