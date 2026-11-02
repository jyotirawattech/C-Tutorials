# 1768 — Merge Strings Alternately

[Problem](https://leetcode.com/problems/merge-strings-alternately/) · [Accepted submission](https://leetcode.com/submissions/detail/2041859979/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 108 / 108 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 22, 2026 13:30**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Advance one cursor through each string and append one character from each while both still have characters. Once a string ends, copy the remaining suffix of the other string. Append a terminator after the combined prefix reaches the sum of the two lengths.

## Complexity

- Time: O(a+b), for input string lengths a and b, including their initial length scans.
- Auxiliary space / ownership: O(1) auxiliary cursors, plus O(a+b) returned string.

## Assumptions and review notes

Requires valid terminated strings and combined lengths representable by int and the allocation size calculation. Allocation failure is checked; the caller owns the result. Exercise equal-length strings, unequal tails and an empty string where the calling contract permits it.

- String termination and integer-length preconditions

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
