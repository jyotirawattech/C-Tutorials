# 2043 — Simple Bank System

[Problem](https://leetcode.com/problems/simple-bank-system/) · [Accepted submission](https://leetcode.com/submissions/detail/2029605836/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 23 / 23 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 11, 2026 15:43**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Keep the supplied balances array and validate one-based account numbers before indexing it. Transfers and withdrawals additionally check available funds before applying their balance changes. Each successful operation updates only the account slots involved.

## Complexity

- Time: O(1) construction, deposit, withdraw and transfer
- Auxiliary space / ownership: O(1) auxiliary object; the caller's existing n-element balance array is borrowed

## Assumptions and review notes

The object aliases and mutates the caller's balances, which must stay alive until bankFree. Nonnegative money and bounded sums are assumed; negative values or signed overflow outside that domain are not rejected, and bankFree does not free the borrowed array.

- Unchecked Bank allocation.
- No negative-money or arithmetic-overflow validation for use outside the judged contract.
- No persistence, authentication, concurrency or production-banking safety is provided.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
