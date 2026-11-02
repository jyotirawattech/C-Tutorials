# 1200 — Minimum Absolute Difference

[Problem](https://leetcode.com/problems/minimum-absolute-difference/) · [Accepted submission](https://leetcode.com/submissions/detail/2040527387/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 39 / 39 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 21, 2026 09:30**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Sort the values so a closest pair must be adjacent. A first pass finds the smallest adjacent difference and counts its occurrences; a second pass allocates and fills exactly those pairs. Relational comparisons in the sort comparator avoid subtraction overflow there.

## Complexity

- Time: O(n log n) under the usual qsort model, plus O(n) scans; qsort's implementation is not prescribed by the C standard.
- Auxiliary space / ownership: O(k) returned pairs/metadata for k matches, plus implementation-dependent qsort workspace.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Compare all unordered value pairs. Examine each pair to find the minimum absolute difference and collect all matching pairs.

- Baseline time: O(n^2). Space: Output storage plus O(1) comparison state.
- Submitted approach: Sort and compare adjacent values. Time: Usually O(n log n), then two O(n) scans. Space: Output storage plus qsort-dependent workspace.

**How much, by analysis:** The baseline evaluates n(n-1)/2 pairs. After sorting, the archive examines n-1 adjacent differences in each of two passes; sorting remains part of the cost, so these counts are not a speed ratio.

**Why:** For sorted distinct values, a minimum-difference pair is adjacent, so nonadjacent pair comparisons are unnecessary.

**Trade-offs and conditions:** Mutates input order and relies on bounded int differences and successful allocations. C does not specify qsort's algorithmic bound; small inputs may not benefit from sorting overhead.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2040527387/) displayed the following at capture on **2026-11-02T13:50:31.890Z**:

- Runtime: **31 ms**; reported runtime `Beats`: **30.56%**.
- Memory: **21.59 MB**; reported memory `Beats`: **53.70%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Mutates the array order and assumes at least two values. Difference calculations still use int subtraction and require the platform's bounded values even though the comparator itself is overflow-safe. Allocations are unchecked; the caller must free every row and both metadata arrays.

- Unchecked allocations
- In-place sorting
- Adjacent-difference overflow outside constrained domain

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
