# 0645 — Set Mismatch

[Problem](https://leetcode.com/problems/set-mismatch/) · [Accepted submission](https://leetcode.com/submissions/detail/2032936506/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 49 / 49 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 14, 2026 20:32**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

XOR the supplied values with the expected range 1..n to isolate duplicate XOR missing. Partition both collections using a distinguishing set bit to recover the two candidates. Scan the input once more to decide which candidate is the duplicate.

## Complexity

- Time: O(n), where n=numsSize
- Auxiliary space / ownership: O(1) auxiliary space; a two-integer returned allocation

## Assumptions and review notes

The contract requires exactly one duplicated value and one missing value in the range 1..n. The returned pair is heap allocated and must be freed by the caller; allocation failure is not checked.

- Unchecked result malloc.
- Unsigned negation is used for bit isolation; the assigned int mask still relies on the bounded problem domain for a straightforward portable interpretation.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
