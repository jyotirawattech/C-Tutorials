# 1590 — Make Sum Divisible by P

[Problem](https://leetcode.com/problems/make-sum-divisible-by-p/) · [Accepted submission](https://leetcode.com/submissions/detail/2040516582/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 145 / 145 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 21, 2026 09:22**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Compute the total remainder modulo p, then scan prefix remainders. For each prefix, look up the complementary earlier remainder whose removal would cancel the total remainder. Store the most recent index for every remainder so matching candidates are as short as possible, and reject removal of the full array.

## Complexity

- Time: Expected O(n+H) with distributed hash chains, O(n^2+H) worst case from collisions; H=100003 bucket slots.
- Auxiliary space / ownership: O(H+min(n+1,p)) for hash buckets and distinct prefix-remainder nodes.

## Assumptions and review notes

Assumes p>0, nonnegative problem values, and a total fitting long long. Allocations are unchecked; negative values could create negative hash indices under C remainder rules. Exercise an already-divisible total, a single-element valid removal and a case requiring forbidden whole-array removal.

- Unchecked malloc/calloc results
- Positive-modulus/nonnegative-input assumptions
- Worst-case hash collisions

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
