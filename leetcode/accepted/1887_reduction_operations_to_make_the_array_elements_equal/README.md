# 1887 — Reduction Operations to Make the Array Elements Equal

[Problem](https://leetcode.com/problems/reduction-operations-to-make-the-array-elements-equal/) · [Accepted submission](https://leetcode.com/submissions/detail/2040528794/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 78 / 78 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 21, 2026 09:32**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Sort the values so equal values form adjacent groups. Increase a tier counter whenever a larger distinct value starts, then add that tier to each element's operation cost. The counter records how many lower distinct levels that element must pass before matching the minimum.

## Complexity

- Time: O(n log n) with a qsort implementation providing that sorting bound, plus an O(n) scan; C does not mandate qsort's worst-case complexity
- Auxiliary space / ownership: qsort workspace is implementation-dependent; the explicit accumulation uses O(1) state

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Simulate every reduction with a full-array maximum search. For each legal operation, scan to find the current largest and next distinct largest, then change one occurrence.

- Baseline time: O(n*T) for T reduction operations; O(n^3) upper bound when T=O(n^2). Space: O(1) auxiliary.
- Submitted approach: Sort once and accumulate distinct-value tiers. Time: O(n log n) with a qsort implementation providing that sorting bound, plus an O(n) scan; C does not mandate qsort's worst-case complexity. Space: qsort workspace is implementation-dependent; the explicit accumulation uses O(1) state.

**How much, by analysis:** With all values distinct, T=n(n-1)/2 individual reductions. This archive does one sort and n-1 adjacent-level updates/accumulations after sorting. It skips explicit simulation of T reductions, but sort/library costs prevent a fixed runtime factor.

**Why:** A value's rank among distinct levels directly counts how many reductions it needs, so the operations need not be performed one at a time.

**Trade-offs and conditions:** Mutates input and relies on qsort's actual algorithm/workspace. The int total assumes bounded problem sizes.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2040528794/) displayed the following at capture on **2026-11-02T13:50:26.794Z**:

- Runtime: **75 ms**; reported runtime `Beats`: **43.75%**.
- Memory: **18.10 MB**; reported memory `Beats`: **22.92%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

The input is sorted in place and the operation total is held in int under the judged bounds. The comparator uses ordered comparisons rather than potentially overflowing subtraction.

- No heap allocation or dangerous string operation in this fragment.
- No overflow checks for totals outside the bounded problem contract.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
