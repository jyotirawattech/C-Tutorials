# 0355 — Design Twitter

[Problem](https://leetcode.com/problems/design-twitter/) · [Accepted submission](https://leetcode.com/submissions/detail/2029610348/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 20 / 20 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 11, 2026 15:47**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Keep a follow matrix and a ten-slot circular tweet buffer for each user. A feed request collects retained tweets from the user and followed accounts, performs at most ten left-to-right descending bubble passes, and returns the first ten IDs. The bounded partial sort has a static correctness concern described below.

## Complexity

- Time: post/follow/unfollow: O(1); feed: O(U + 10T), where U=500 candidate users and T<=10U retained candidate tweets
- Auxiliary space / ownership: Per object O(U^2 + 10U); feed temporary O(T), plus at most ten returned IDs

## Assumptions and review notes

A private focused harness confirmed the partial-sort defect. After users 1,2,3 each post ten tweets in that order and user 1 follows 2 and 3, the newest ten IDs should be 309..300; this source returns 209..200. Historical platform Accepted metadata is preserved, but this implementation is not freshly endorsed as correct.

- Unchecked calloc/malloc results.
- Fixed valid user-ID domain 1..500 and signed timestamp/count growth are assumed.
- Source comment calls sorting 'Extremely fast'; no benchmark or hardware claim is established.

Problem355 has a [reproduced feed-order issue](../../review/README.md); the original source is retained unchanged.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
