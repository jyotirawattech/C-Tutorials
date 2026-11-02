# 3754 — Concatenate Non-Zero Digits and Multiply by Sum I

[Problem](https://leetcode.com/problems/concatenate-non-zero-digits-and-multiply-by-sum-i/) · [Accepted submission](https://leetcode.com/submissions/detail/2058859407/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 954 / 954 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jul 07, 2026 11:39**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Peel decimal digits from right to left. For each nonzero digit, add it at the next retained place value and accumulate its digit sum; skipped zeros do not advance that place value. Multiplying the retained-digit number by the sum yields the result.

## Complexity

- Time: O(d), where d is the number of decimal digits in n.
- Auxiliary space / ownership: O(1) auxiliary storage.

## Assumptions and review notes

Implements the nonnegative-int input case and relies on the documented maximum for long long arithmetic. A zero input returns zero; negative inputs also return zero but are outside the intended contract. Exercise internal zeros, trailing zeros and an all-nonzero input.

- Integer range assumptions; no arbitrary-precision support

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
