# 0122 — Best Time to Buy and Sell Stock II

[Problem](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/) · [Accepted submission](https://leetcode.com/submissions/detail/450652093/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 200 / 200 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Feb 01, 2021 22:44**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Add every positive difference between consecutive prices. Each rising segment can be decomposed into those adjacent gains without changing its total profit, while falling steps are ignored. The running total therefore captures all profitable increases under unlimited transactions with no fee or cooldown.

## Complexity

- Time: O(n), where n is the number of prices.
- Auxiliary space / ownership: O(1) auxiliary storage.

## How this solution compares

**Conclusion:** Improvement not established.

**Named baseline:** Two-state stock dynamic programming. Track best cash and held-stock values for each day under unlimited fee-free transactions.

- Baseline time: O(n). Space: O(1) with rolling states.
- Submitted approach: Sum positive adjacent gains. Time: O(n). Space: O(1).

**How much, by analysis:** Both visit every price once and use constant state. The archive uses a positive-difference accumulation instead of two DP states, but no measured constant-factor advantage is established.

**Why:** Without fees, cooldowns or transaction limits, all positive adjacent changes telescope to the profit of rising runs.

**Trade-offs and conditions:** The simpler greedy form cannot be transferred unchanged to fees/cooldowns/limited transactions. It reads prices[0], requiring nonempty input.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/450652093/) displayed the following at capture on **2026-11-02T13:46:21.332Z**:

- Runtime: **4 ms**; reported runtime `Beats`: **2.69%**.
- Memory: **6.73 MB**; reported memory `Beats`: **100.00%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Reads prices[0] before the loop, so the input must be nonempty. The result uses int and assumes problem-bounded cumulative gain; transaction fees, cooldowns and transaction limits require a different model.

- Nonempty input precondition
- Profit accumulation relies on integer bounds

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
