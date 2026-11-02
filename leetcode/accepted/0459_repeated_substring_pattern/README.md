# 0459 — Repeated Substring Pattern

[Problem](https://leetcode.com/problems/repeated-substring-pattern/) · [Accepted submission](https://leetcode.com/submissions/detail/2033708350/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 130 / 130 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 15, 2026 14:21**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Build the KMP longest-proper-prefix/suffix table for every prefix of the string. The final table value identifies a possible repeating block of length n-lps[n-1]. A nonzero border and exact divisibility by that block length establish repetition.

## Complexity

- Time: O(n), where n is string length; fallback transitions are amortized linear
- Auxiliary space / ownership: O(n) auxiliary LPS array

## Assumptions and review notes

The string must be valid and NUL terminated with length fitting int. Allocation failure returns false, which is indistinguishable from a genuinely nonrepeating string.

- Uses strlen, flagged by selected safe-C guidance; preserved as historical source.
- Allocation failure is checked but conflated with a valid false result.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
