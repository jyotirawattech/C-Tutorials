# 0121 — Best Time to Buy and Sell Stock

[Problem](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) · [Accepted submission](https://leetcode.com/submissions/detail/2046785680/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 212 / 212 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 26, 2026 17:29**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Track the minimum price in the processed prefix and the best nonnegative profit found so far. A new minimum replaces the buy candidate; otherwise the current price is compared with that minimum as a possible later sale. This preserves the buy-before-sell order without storing all pairs.

## Complexity

- Time: O(n), where n=pricesSize
- Auxiliary space / ownership: O(1) auxiliary space

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Enumerate all buy-before-sell pairs. Evaluate every i<j trade and retain the largest nonnegative profit.

- Baseline time: O(n^2). Space: O(1).
- Submitted approach: Running prefix minimum. Time: O(n), where n=pricesSize. Space: O(1) auxiliary space.

**How much, by analysis:** A complete pair enumeration evaluates n(n-1)/2 candidate trades; the scan processes n-1 later days. For n>=2 those candidate/scan counts differ by n/2, but the steps are different operations and this is not an n/2 elapsed-time claim.

**Why:** The best purchase price for a sale day is summarized by the minimum of the earlier prefix.

**Trade-offs and conditions:** Both use constant auxiliary space. The scan depends on valid bounded prices for its int arithmetic and supplies only the profit, not the chosen days.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2046785680/) displayed the following at capture on **2026-11-02T13:47:21.321Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **15.94 MB**; reported memory `Beats`: **72.44%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

The function assumes a readable price array and the problem's bounded price domain for safe int differences. Declining, constant-price and one-day inputs should return zero; arbitrary integer extremes are outside the archived contract.

- No allocation or dangerous library call observed.
- Source 'hardware safety'/'state registers' language does not establish actual register placement or hardware guarantees.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
