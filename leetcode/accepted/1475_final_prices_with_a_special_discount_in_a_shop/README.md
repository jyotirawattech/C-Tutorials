# 1475 — Final Prices With a Special Discount in a Shop

[Problem](https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/) · [Accepted submission](https://leetcode.com/submissions/detail/2033027189/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 103 / 103 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 14, 2026 22:09**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Keep indices waiting for their first later price that is less than or equal to their original price. When such a price arrives, pop matching pending indices and subtract the current price directly in the input array. Remaining pending indices keep their original values because no eligible later discount was found.

## Complexity

- Time: O(n) amortized, where n=pricesSize; each index enters and leaves the stack at most once
- Auxiliary space / ownership: O(n) auxiliary stack; the returned pointer aliases the existing input array

## Assumptions and review notes

The function mutates prices and returns that same pointer, despite the generic comment about a malloc-allocated return. Do not free the result separately from the input or assume an independent copy; the stack allocation is also unchecked.

- Unchecked stack malloc.
- Generic malloc-return comment is inconsistent with the actual returned input alias.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
