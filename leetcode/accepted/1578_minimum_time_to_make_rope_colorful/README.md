# 1578 — Minimum Time to Make Rope Colorful

[Problem](https://leetcode.com/problems/minimum-time-to-make-rope-colorful/) · [Accepted submission](https://leetcode.com/submissions/detail/462403664/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 113 / 113 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Mar 02, 2021 09:51**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Scan adjacent equal-colored balloons and add the smaller removal cost. Propagate the larger surviving cost across each equal-color run, so subsequent comparisons retain the most expensive balloon and remove all cheaper ones. The accumulated cost is the total run cost minus its maximum.

## Complexity

- Time: O(n), where n is costSize and the matching color-string length.
- Auxiliary space / ownership: O(1) auxiliary storage.

## How this solution compares

**Conclusion:** Same or worse against this comparator.

**Named baseline:** Nonmutating run sum minus run maximum. For every same-color run, add its total cost minus its largest cost.

- Baseline time: O(n). Space: O(1).
- Submitted approach: Propagate the surviving maximum cost. Time: O(n). Space: O(1).

**How much, by analysis:** Both examine n-1 adjacency relationships with linear work. The archive additionally mutates some cost entries; no asymptotic storage or measured timing advantage over the nonmutating baseline is established.

**Why:** Both keep the most expensive balloon in each run and remove the others. The archived propagation uses writes into the cost array rather than only local run totals.

**Trade-offs and conditions:** The input cost array is changed. A nonmutating run-based method retains the same complexity while preserving callers' data.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/462403664/) displayed the following at capture on **2026-11-02T13:46:18.221Z**:

- Runtime: **124 ms**; reported runtime `Beats`: **0.00%**.
- Memory: **14.65 MB**; reported memory `Beats`: **100.00%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Mutates the supplied cost array to propagate run maxima. Assumes a valid color string with at least costSize characters and a total fitting int; exercise all-equal colors, already alternating colors, and a single balloon.

- In-place cost mutation
- String length and integer-sum constraints

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
