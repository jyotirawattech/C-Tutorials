# 2144 — Minimum Cost of Buying Candies With Discount

[Problem](https://leetcode.com/problems/minimum-cost-of-buying-candies-with-discount/) · [Accepted submission](https://leetcode.com/submissions/detail/2046771410/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 192 / 192 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 26, 2026 17:12**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Count candy prices in a bounded frequency array and visit prices in descending order. Pay for two candies, then take the next candy free, repeating that three-item cycle. Processing larger prices first ensures the free item never exceeds either paid item and maximizes the useful discount.

## Complexity

- Time: O(n+V), for n candies and the fixed price domain V=100.
- Auxiliary space / ownership: O(V) frequency storage, constant for the implemented domain.

## Assumptions and review notes

Direct indexing assumes prices in 1..100, and the running total relies on problem integer bounds. The source's exact byte-size and guaranteed-cache-hit claims are platform-dependent or unmeasured, not benchmark evidence. Exercise one/two candies and duplicate prices across discount groups.

- Fixed price-domain indexing
- Unverified cache and platform-size commentary

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
