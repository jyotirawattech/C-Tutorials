# 0088 — Merge Sorted Array

[Problem](https://leetcode.com/problems/merge-sorted-array/) · [Accepted submission](https://leetcode.com/submissions/detail/2033796939/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 59 / 59 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 15, 2026 15:40**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Read the largest remaining values from the ends of the two sorted inputs and write the larger one into the last unused destination slot. Working backward avoids overwriting unread values in nums1. When nums2 is exhausted, any remaining nums1 prefix is already in place.

## Complexity

- Time: O(m+n), for m initial nums1 values and n nums2 values.
- Auxiliary space / ownership: O(1) auxiliary storage.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Forward merge with copied first input. Copy nums1's m live values into a temporary array, then merge forward into nums1.

- Baseline time: O(m+n). Space: O(m) auxiliary copy.
- Submitted approach: Backward merge into spare capacity. Time: O(m+n). Space: O(1) auxiliary pointers.

**How much, by analysis:** The archive avoids copying and storing m temporary integers while retaining linear merge work. The baseline and archive have equal time-growth order; no measured faster percentage is established.

**Why:** Writing from the end protects unread nums1 values and removes the need for the temporary copy.

**Trade-offs and conditions:** Requires at least m+n destination slots and valid sorted inputs; supplied capacity parameters are trusted rather than checked.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2033796939/) displayed the following at capture on **2026-11-02T13:51:58.171Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **10.76 MB**; reported memory `Beats`: **29.02%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Requires sorted inputs, destination capacity at least m+n, and a nums2 source not improperly overlapping the destination. The function ignores the supplied capacity parameters and trusts m/n. Exercise an empty first logical array and a second array whose values all precede the first.

- Unchecked caller-provided lengths/capacity
- In-place destination mutation

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
