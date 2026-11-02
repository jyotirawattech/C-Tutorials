# 0198 — House Robber

[Problem](https://leetcode.com/problems/house-robber/) · [Accepted submission](https://leetcode.com/submissions/detail/2046775170/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 70 / 70 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 26, 2026 17:16**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Track the best totals for the previous two prefixes. At each house, choose between skipping it and adding its value to the best total that ends before the adjacent house. Shift those two states forward, keeping the invariant that the stored best total never includes adjacent selected houses.

## Complexity

- Time: O(n), where n is the number of houses.
- Auxiliary space / ownership: O(1) auxiliary state.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Full prefix-DP table. Store the best nonadjacent total for every prefix.

- Baseline time: O(n). Space: O(n) DP table.
- Submitted approach: Rolling two-prefix DP. Time: O(n). Space: O(1).

**How much, by analysis:** The archive replaces n stored DP values with two rolling values and a temporary current value. Both compute n recurrence steps; this is a storage reduction, not a measured runtime gain.

**Why:** The recurrence only reads the previous two prefix optima, so older table cells are unnecessary when only the total is returned.

**Trade-offs and conditions:** The chosen-house sequence is not retained for reconstruction. Nonnegative values and bounded integer totals are assumed.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2046775170/) displayed the following at capture on **2026-11-02T13:48:13.290Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **8.76 MB**; reported memory `Beats`: **52.48%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Assumes the problem's nonnegative values and an optimal sum fitting int. Empty input returns zero; a single element returns that element directly. Exercise zero-valued houses and cases where taking a locally larger value blocks a better later combination.

- Integer-sum bound and nonnegative-value assumptions

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
