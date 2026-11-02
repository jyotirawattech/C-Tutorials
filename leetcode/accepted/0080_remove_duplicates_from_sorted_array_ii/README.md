# 0080 — Remove Duplicates from Sorted Array II

[Problem](https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/) · [Accepted submission](https://leetcode.com/submissions/detail/2035107421/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 170 / 170 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 16, 2026 17:14**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Maintain a compacted sorted prefix containing at most two copies of each value. For each scanned value, keep it only when it differs from the value two positions before the write cursor. The returned cursor gives the usable prefix length while unused suffix contents remain unspecified.

## Complexity

- Time: O(n), where n is the input length.
- Auxiliary space / ownership: O(1) auxiliary storage.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Collect allowed duplicates in a temporary array. Scan sorted input, keep at most two copies per value in another array, then copy back.

- Baseline time: O(n). Space: O(n) temporary storage.
- Submitted approach: Two-behind in-place compaction. Time: O(n). Space: O(1) auxiliary storage.

**How much, by analysis:** For n>2 the archive inspects n-2 scanned positions and avoids an n-element temporary buffer and copy-back pass. Both methods remain linear; no elapsed-time ratio is available.

**Why:** Comparing with the retained value two slots behind the write cursor enforces the duplicate limit without another array.

**Trade-offs and conditions:** Sorted input and permission to overwrite its prefix are required. The archive is not asymptotically better than other in-place linear solutions.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2035107421/) displayed the following at capture on **2026-11-02T13:51:31.808Z**:

- Runtime: **33 ms**; reported runtime `Beats`: **17.35%**.
- Memory: **15.22 MB**; reported memory `Beats`: **13.26%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Requires sorted input and mutates its prefix in place. Inputs of length at most two are returned unchanged. Exercise all-equal values and runs of exactly two versus three copies; consumers must use only the returned logical length.

- Sorted-input precondition
- In-place compaction

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
