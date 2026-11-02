"""Synthetic comparison fixtures exercise evidence gates, not real benchmark claims."""
import copy
import json
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import check_comparisons as comparisons
import test_archive_integrity as archive_tests


class ComparisonEvidenceTests(unittest.TestCase):
    def setUp(self):
        self.fixture = archive_tests.ArchiveIntegrityTests()
        self.fixture.setUp()
        self.addCleanup(self.fixture.doCleanups)
        self.root, self.folder = self.fixture.root, self.fixture.folder
        metadata = self.fixture.metadata
        self.comparison = {
            "problem_id": metadata["problem_id"], "source_sha256": metadata["source_sha256"],
            "source_submission_url": metadata["submission_url"],
            "baseline": {"name": "Exhaustive pairs", "approach": "Check every valid pair",
                         "time": "O(n^2)", "space": "O(1)"},
            "archived": {"name": "One scan", "time": "O(n)", "space": "O(1)"},
            "why": "Retain the best prefix state instead of enumerating pairs.",
            "quantitative_comparison": "Theoretical work is n(n-1)/2 pairs versus n scan steps.",
            "tradeoffs": "The model assumes the stated constraints; no paired timing was run.",
            "verdict": "advantage_with_conditions",
            "evidence_basis": "Theoretical work model and a dated LeetCode UI snapshot; no paired benchmark.",
            "judge_snapshot": {
                "runtime_display": "0", "runtime_unit": "ms",
                "runtime_beats_display": "100.00%", "memory_display": "15.94",
                "memory_unit": "MB", "memory_beats_display": "72.44%",
                "captured_at": metadata["captured_at"],
                "source_submission_url": metadata["submission_url"],
            },
            "paired_benchmark": {"status": "not_run", "speedup_factor": None,
                                 "memory_reduction_percent": None},
        }
        self.write()

    def write(self):
        (self.folder / "comparison.json").write_text(json.dumps(self.comparison))

    def check(self, raw_dir=None, expected_count=1):
        return comparisons.validate_comparisons(self.root, expected_count, raw_dir)

    def test_zero_ms_ui_snapshot_is_valid_without_numeric_speedup(self):
        self.assertTrue(self.check()["comparison_evidence_passed"])

    def test_source_identity_mismatch_fails(self):
        for key, value in [("problem_id", 2), ("source_sha256", "0" * 64),
                           ("source_submission_url", "https://leetcode.com/submissions/detail/999/")]:
            with self.subTest(key=key):
                old = self.comparison[key]
                self.comparison[key] = value
                self.write()
                self.assertFalse(self.check()["comparison_evidence_passed"])
                self.comparison[key] = old

    def test_coverage_and_source_tampering_fail(self):
        self.assertFalse(self.check(expected_count=2)["comparison_evidence_passed"])
        (self.folder / "submission.c").write_text("int changed(void) { return 0; }")
        self.assertFalse(self.check()["comparison_evidence_passed"])

    def test_baseline_and_bounds_are_required(self):
        original = copy.deepcopy(self.comparison)
        for section, key in [("baseline", "approach"), ("baseline", "time"),
                             ("archived", "space")]:
            self.comparison = copy.deepcopy(original)
            self.comparison[section].pop(key)
            self.write()
            self.assertFalse(self.check()["comparison_evidence_passed"])
        self.comparison = copy.deepcopy(original)
        self.comparison.pop("baseline")
        self.write()
        self.assertFalse(self.check()["comparison_evidence_passed"])

    def test_invalid_units_and_percentile_values_fail(self):
        snap = self.comparison["judge_snapshot"]
        for key, value in [("runtime_unit", "seconds"), ("memory_unit", "KB"),
                           ("runtime_beats_display", "100.01%"),
                           ("memory_beats_display", "-1%"),
                           ("runtime_display", 0), ("memory_display", "NaN")]:
            with self.subTest(key=key):
                old = snap[key]
                snap[key] = value
                self.write()
                self.assertFalse(self.check()["comparison_evidence_passed"])
                snap[key] = old

        snap["derived_speedup"] = 999
        self.write()
        self.assertFalse(self.check()["comparison_evidence_passed"])

    def test_capture_clock_and_snapshot_source_are_required(self):
        snap = self.comparison["judge_snapshot"]
        for key, value in [("captured_at", ""), ("captured_at", "2026-11-02"),
                           ("source_submission_url", "https://leetcode.com/submissions/detail/999/")]:
            with self.subTest(key=key):
                old = snap[key]
                snap[key] = value
                self.write()
                self.assertFalse(self.check()["comparison_evidence_passed"])
                snap[key] = old

    def test_fabricated_numeric_benchmark_fields_fail(self):
        paired = self.comparison["paired_benchmark"]
        for key, value in [("speedup_factor", 2), ("memory_reduction_percent", 50),
                           ("status", "measured")]:
            with self.subTest(key=key):
                old = paired[key]
                paired[key] = value
                self.write()
                self.assertFalse(self.check()["comparison_evidence_passed"])
                paired[key] = old

        paired["unverified_gain"] = 20
        self.write()
        self.assertFalse(self.check()["comparison_evidence_passed"])

    def test_percentile_as_percent_faster_and_zero_division_claims_fail(self):
        for claim in ["72.44% faster than other solutions",
                      "Measured speedup factor: 2",
                      "2x faster than the baseline",
                      "10 / 0 ms = infinite speedup",
                      "0 ms means instant execution"]:
            with self.subTest(claim=claim):
                self.comparison["quantitative_comparison"] = claim
                self.write()
                self.assertFalse(self.check()["comparison_evidence_passed"])

    def test_unknown_same_or_worse_and_correctness_limit_are_valid(self):
        for verdict in comparisons.VERDICTS:
            self.comparison["verdict"] = verdict
            self.write()
            self.assertTrue(self.check()["comparison_evidence_passed"])

    def test_private_ui_metrics_must_match_exact_displays(self):
        raw_dir = self.root / "private"
        raw_dir.mkdir()
        raw = {
            "id": 1, "owner_url": comparisons.accepted.OWNER,
            "language_class": "language-c", "code": self.fixture.source,
            "submission_url": self.fixture.metadata["submission_url"],
            "observed_at": self.fixture.metadata["captured_at"],
            "prelude": "Accepted\nRuntime\n0\nms\nBeats\n100.00%\nMemory\n15.94\nMB\nBeats\n72.44%",
        }
        (raw_dir / "0001.json").write_text(json.dumps(raw))
        self.assertTrue(self.check(raw_dir)["comparison_evidence_passed"])
        self.comparison["judge_snapshot"]["runtime_beats_display"] = "99.99%"
        self.write()
        self.assertFalse(self.check(raw_dir)["comparison_evidence_passed"])


if __name__ == "__main__":
    unittest.main()
