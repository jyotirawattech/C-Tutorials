# 1071 — Greatest Common Divisor of Strings

[Problem](https://leetcode.com/problems/greatest-common-divisor-of-strings/) · [Accepted submission](https://leetcode.com/submissions/detail/2041863308/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 128 / 128 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 22, 2026 13:33**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Check whether the two virtual concatenations str1+str2 and str2+str1 match without allocating either concatenation. If they commute, the greatest common divisor of their lengths gives the repeating divisor's length. Return a newly allocated copy of that prefix, or a newly allocated empty string on mismatch.

## Complexity

- Time: O(n+m), where n and m are the string lengths; Euclidean length-GCD work is dominated by that scan
- Auxiliary space / ownership: O(1) explicit auxiliary state plus O(g) returned string, where g=gcd(n,m)

## Assumptions and review notes

Inputs must be valid NUL-terminated strings with lengths fitting int. The mismatch path writes through an unchecked malloc result; the caller owns both nonempty and empty returned strings.

- Unchecked one-byte allocation on the mismatch path.
- Uses strlen and memcpy, flagged by selected safe-C guidance; the historical source is preserved rather than silently replaced.
- Captured fragment lacks string/stdlib declarations and assumes bounded string lengths.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
