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

## Assumptions and review notes

The function assumes a readable price array and the problem's bounded price domain for safe int differences. Declining, constant-price and one-day inputs should return zero; arbitrary integer extremes are outside the archived contract.

- No allocation or dangerous library call observed.
- Source 'hardware safety'/'state registers' language does not establish actual register placement or hardware guarantees.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
