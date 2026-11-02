# 0189 — Rotate Array

[Problem](https://leetcode.com/problems/rotate-array/) · [Accepted submission](https://leetcode.com/submissions/detail/463974219/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 35 / 35 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Mar 06, 2021 01:20**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Reduce the requested rotation count modulo the array length. Perform that many one-position right rotations by saving the first value, moving the last value to the front, shifting the interior, and restoring the saved value into index one. Each completed pass preserves the array's elements while changing their positions by one.

## Complexity

- Time: O(n*(k mod n)), where n=numsSize; worst case O(n^2)
- Auxiliary space / ownership: O(1) auxiliary space; input is modified

## Assumptions and review notes

This is a repeated-shift implementation, not the O(n) three-reversal method. It mutates the caller's array and assumes nonnegative k; zero length is handled before modulo.

- No allocation or dangerous library call observed.
- No new performance measurement is established; large n and k mod n incur repeated full-array shifts.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
