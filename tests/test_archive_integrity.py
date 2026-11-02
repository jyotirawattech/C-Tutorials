"""Synthetic fixtures test the integrity gate; no real acceptance is fabricated."""
import hashlib
import importlib.util
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

SPEC = importlib.util.spec_from_file_location(
    "check_accepted", Path(__file__).resolve().parents[1] / "scripts/check_accepted.py")
archive = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(archive)


class ArchiveIntegrityTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="archive-integrity-test-")
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.relative = "leetcode/accepted/0001_synthetic_fixture"
        self.folder = self.root / self.relative
        self.folder.mkdir(parents=True)
        self.source = "int example(void) { return 1; }"
        self.metadata = {
            "problem_id": 1, "title": "Synthetic fixture", "slug": "synthetic-fixture",
            "problem_url": "https://leetcode.com/problems/synthetic-fixture/",
            "submission_url": "https://leetcode.com/submissions/detail/123/",
            "owner_profile_url": archive.OWNER, "verdict": "Accepted", "language": "C",
            "displayed_submission_time": "Jun 15, 2026 14:00",
            "displayed_timezone": "Unspecified", "original_practice_date": "Unknown",
            "original_assistance": "Unknown", "captured_at": "2026-11-02T13:00:00Z",
            "publication_date": "2026-11-02",
            "source_sha256": hashlib.sha256(self.source.encode()).hexdigest(),
        }
        self.index = {"expected_count": 1, "owner_profile_url": archive.OWNER,
                      "entries": [{"problem_id": 1, "slug": "synthetic-fixture",
                                   "path": self.relative}]}
        self.write_fixture()

    def write_fixture(self):
        (self.root / "leetcode/accepted/index.json").write_text(json.dumps(self.index))
        (self.folder / "metadata.json").write_text(json.dumps(self.metadata))
        (self.folder / "submission.c").write_text(self.source)
        (self.folder / "README.md").write_text(
            self.metadata["problem_url"] + "\n" + self.metadata["submission_url"])

    def check(self, raw_dir=None):
        return archive.validate_archive(self.root, expected_count=1, raw_dir=raw_dir)

    def test_valid_metadata_hash_and_source_links(self):
        self.assertTrue(self.check()["integrity_passed"])

    def test_source_tampering_is_not_accepted(self):
        (self.folder / "submission.c").write_text("int altered(void) { return 2; }")
        self.assertIn("source hash mismatch", " ".join(self.check()["errors"]))

    def test_unindexed_directory_is_a_coverage_gap(self):
        (self.root / "leetcode/accepted/9999_extra").mkdir()
        self.assertIn("coverage mismatch", " ".join(self.check()["errors"]))

    def test_count_and_duplicate_identity_fail(self):
        self.index["entries"].append(self.index["entries"][0].copy())
        self.write_fixture()
        report = self.check()
        self.assertFalse(report["integrity_passed"])
        self.assertIn("coverage", " ".join(report["errors"]))
        self.assertIn("duplicate", " ".join(report["errors"]))

    def test_wrong_owner_or_nonaccepted_verdict_fail(self):
        for key, value in [("owner_profile_url", "https://leetcode.com/u/other/"),
                           ("verdict", "Wrong Answer")]:
            with self.subTest(key=key):
                original = self.metadata[key]
                self.metadata[key] = value
                self.write_fixture()
                self.assertFalse(self.check()["integrity_passed"])
                self.metadata[key] = original

    def test_traversal_is_rejected(self):
        self.index["entries"][0]["path"] = "../outside"
        self.write_fixture()
        self.assertFalse(self.check()["integrity_passed"])
        with self.assertRaises(ValueError):
            archive.safe_file(self.root, "../outside")

    def test_private_capture_comparison_and_wrong_verdict(self):
        raw_dir = self.root / "private"
        raw_dir.mkdir()
        raw = {"id": 1, "title": self.metadata["title"], "slug": self.metadata["slug"],
               "problem_url": self.metadata["problem_url"],
               "submission_url": self.metadata["submission_url"], "code": self.source,
               "owner_url": archive.OWNER, "language_class": "language-c",
               "prelude": "Accepted\n1 / 1 testcases passed\nsubmitted at Jun 15, 2026 14:00",
               "observed_at": self.metadata["captured_at"]}
        (raw_dir / "1.json").write_text(json.dumps(raw))
        self.assertTrue(self.check(raw_dir)["integrity_passed"])
        raw["prelude"] = raw["prelude"].replace("Accepted", "Wrong Answer")
        (raw_dir / "1.json").write_text(json.dumps(raw))
        self.assertFalse(self.check(raw_dir)["integrity_passed"])

    def test_source_review_blocks_process_calls_and_unknown_includes(self):
        self.assertTrue(archive.scan_source("#include <unistd.h>\nint f(void) { return 0; }"))
        self.assertTrue(archive.scan_source('int f(void) { return system("true"); }'))
        self.assertIn("unsupported dependency", " ".join(
            archive.scan_source("#include \"uthash.h\"\nUT_hash_handle hh;")))
        self.assertEqual(archive.scan_source("#include <stdlib.h>\nint f(void) { return 0; }"), [])

    def test_problem_types_are_explicit_and_node_is_only_138(self):
        self.assertEqual(archive.TYPE_FLAGS[106], ["LC_TREE_NODE"])
        self.assertEqual(archive.TYPE_FLAGS[138], ["LC_RANDOM_NODE"])
        self.assertNotIn("LC_RANDOM_NODE", archive.TYPE_FLAGS.get(146, []))

    def test_compile_is_object_only_and_review_blocks_before_subprocess(self):
        entry = self.check()["entries"][0]
        with patch.object(archive.subprocess, "run") as invoke:
            invoke.return_value.returncode = 0
            invoke.return_value.stderr = ""
            result = archive.compile_entry(self.root, entry, "/usr/bin/clang")
            command = invoke.call_args.args[0]
            self.assertEqual(result["status"], "compiled")
            self.assertIn("-c", command)
            self.assertNotIn("-Werror", command)
            self.assertEqual(command[-1].split("/")[-1], "submission.o")
        entry["source_review"] = ["unsupported dependency: uthash.h"]
        with patch.object(archive.subprocess, "run") as invoke:
            self.assertEqual(archive.compile_entry(self.root, entry, "clang")["status"],
                             "blocked_source_review")
            invoke.assert_not_called()


if __name__ == "__main__":
    unittest.main()
