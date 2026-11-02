# 0448 — Find All Numbers Disappeared in an Array

[Problem](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/) · [Accepted submission](https://leetcode.com/submissions/detail/2032943655/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 35 / 35 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 14, 2026 20:41**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Use each value's absolute magnitude as an index into the input and mark that position negative. After marking, the remaining positive positions identify values that were never encountered. Duplicate values preserve the same negative mark instead of reversing it.

## Complexity

- Time: O(n), where n is the input length.
- Auxiliary space / ownership: O(1) auxiliary work space, plus an allocated result buffer of O(n).

## Assumptions and review notes

Mutates the input signs and requires every original value to be in 1..n. Values outside that range can index out of bounds, and abs(INT_MIN) is invalid; the problem constraints exclude those cases. The caller owns the returned allocation.

- Unchecked malloc result
- In-place mutation
- Indexing and abs rely on constrained positive input

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
