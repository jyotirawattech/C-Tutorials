# 1365 — How Many Numbers Are Smaller Than the Current Number

[Problem](https://leetcode.com/problems/how-many-numbers-are-smaller-than-the-current-number/) · [Accepted submission](https://leetcode.com/submissions/detail/2032937879/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 103 / 103 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 14, 2026 20:34**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Count occurrences in the fixed 0..100 value domain. Replace each frequency with the number of values strictly below it by scanning the buckets in order. A final lookup per original value produces the count while preserving input order.

## Complexity

- Time: O(n+U), where n=numsSize and U=101 buckets; O(n) for this fixed domain
- Auxiliary space / ownership: O(U) auxiliary bucket storage and O(n) returned result; O(1) auxiliary for fixed U=101

## Assumptions and review notes

An input outside 0..100 indexes beyond the frequency array. The source assumes the bounded domain and a successful result allocation rather than validating either.

- Unchecked result malloc.
- Array indexing directly uses unvalidated input values under the problem contract.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
