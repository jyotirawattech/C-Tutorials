# 3756 — Concatenate Non-Zero Digits and Multiply by Sum II

[Problem](https://leetcode.com/problems/concatenate-non-zero-digits-and-multiply-by-sum-ii/) · [Accepted submission](https://leetcode.com/submissions/detail/2060383645/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 523 / 523 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jul 08, 2026 16:04**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Precompute prefix digit sums, counts of retained nonzero digits, retained-digit values modulo 1000000007, and powers of ten. For each range, subtract the earlier retained prefix after shifting it by the range's nonzero-digit count, then multiply by the range's digit sum. Modular normalization handles a negative subtraction before multiplication.

## Complexity

- Time: O(m + q), for string length m and q queries.
- Auxiliary space / ownership: O(m) auxiliary prefix arrays and O(q) returned answers.

## Assumptions and review notes

Requires a terminated decimal string, valid inclusive query bounds, and problem-bounded arithmetic. If any allocation fails, the early NULL return leaks allocations that already succeeded; normal completion frees the four auxiliary arrays. The source's kernel-panic/stack commentary is not verified and does not describe ordinary user-space stack failure accurately.

- Known partial-allocation failure leak
- Requires platform-provided string/allocation declarations or wrapper
- Unverified hardware/kernel-panic commentary

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
