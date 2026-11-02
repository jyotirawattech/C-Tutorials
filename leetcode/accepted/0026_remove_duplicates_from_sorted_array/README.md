# 0026 — Remove Duplicates from Sorted Array

[Problem](https://leetcode.com/problems/remove-duplicates-from-sorted-array/) · [Accepted submission](https://leetcode.com/submissions/detail/2035054515/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 362 / 362 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 16, 2026 16:19**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Keep the last unique value at a slow write position while a fast cursor scans the sorted array. Copy a value forward only when it differs from that last unique value. Return the length of the compacted unique prefix; the suffix is outside the result contract.

## Complexity

- Time: O(n), where n is the input length.
- Auxiliary space / ownership: O(1) auxiliary storage.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Erase duplicate entries one at a time. On finding a duplicate in a sorted array, shift the remaining suffix left.

- Baseline time: O(n^2) worst case. Space: O(1).
- Submitted approach: Two-cursor prefix compaction. Time: O(n). Space: O(1).

**How much, by analysis:** For nonempty input the archive scans exactly n-1 following values; repeated deletion can perform a quadratic number of element moves. This is a work/growth comparison, not a measured speedup.

**Why:** A write cursor copies each new unique value once instead of shifting a suffix after every removal.

**Trade-offs and conditions:** Both approaches mutate the input and require sorted order. The archive leaves the unused suffix unspecified and has the same growth rate as other standard linear compaction methods.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2035054515/) displayed the following at capture on **2026-11-02T13:51:36.266Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **12.90 MB**; reported memory `Beats`: **57.76%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Requires sorted input and mutates its prefix. Empty input returns zero. Exercise a single repeated run and an already unique array, and use only the returned logical length.

- Sorted-input precondition
- In-place compaction

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
