# 0041 — First Missing Positive

[Problem](https://leetcode.com/problems/first-missing-positive/) · [Accepted submission](https://leetcode.com/submissions/detail/2037084114/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 179 / 179 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 18, 2026 10:44**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Place each value x in 1..n into slot x-1 by swapping, skipping values already at their correct destination to avoid duplicate loops. Every successful swap permanently positions at least one valid value. The first slot not containing its expected positive value identifies the missing number; otherwise return n+1.

## Complexity

- Time: O(n) amortized, where n=numsSize
- Auxiliary space / ownership: O(1) auxiliary space; input is rearranged

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Presence bitmap for values 1..n. Allocate n+1 markers, record valid values, then scan for the first missing marker.

- Baseline time: O(n). Space: O(n) auxiliary markers.
- Submitted approach: Cyclic placement in the input array. Time: O(n) amortized, where n=numsSize. Space: O(1) auxiliary space; input is rearranged.

**How much, by analysis:** The bitmap stores n+1 markers. The archived method keeps constant state and makes at most n successful value-placement swaps before a linear scan. Both have linear growth in work; the established advantage is auxiliary storage, not a measured speed factor.

**Why:** The input slots themselves encode which positive values are present, so a separate presence array is unnecessary.

**Trade-offs and conditions:** Rearranges the caller's array. A bitmap can preserve input order and is often easier to audit; valid indexing and the duplicate guard are essential in cyclic placement.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2037084114/) displayed the following at capture on **2026-11-02T13:51:18.015Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **14.52 MB**; reported memory `Beats`: **51.89%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

The function mutates the array and assumes a valid writable buffer. The range checks precede derived indexing, while the duplicate-destination check is essential for termination.

- No allocation or dangerous library call observed.
- numsSize+1 assumes a bounded problem length rather than arbitrary INT_MAX-sized input.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
