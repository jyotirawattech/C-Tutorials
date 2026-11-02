# 1929 — Concatenation of Array

[Problem](https://leetcode.com/problems/concatenation-of-array/) · [Accepted submission](https://leetcode.com/submissions/detail/2031672202/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 92 / 92 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 13, 2026 16:05**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Allocate a result with room for twice the input length. Copy each input value into its corresponding position in both halves of that result. The result's first and second n-element segments each reproduce the original array.

## Complexity

- Time: O(n), where n=numsSize
- Auxiliary space / ownership: O(1) auxiliary state plus O(n) returned storage

## Assumptions and review notes

The caller owns the newly allocated result and must free it. The source assumes allocation succeeds and that twice the length and allocation-size arithmetic fit the judged input bounds.

- Unchecked result malloc.
- No overflow checks for numsSize*2 outside the bounded problem domain.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
