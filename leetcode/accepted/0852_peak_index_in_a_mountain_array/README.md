# 0852 — Peak Index in a Mountain Array

[Problem](https://leetcode.com/problems/peak-index-in-a-mountain-array/) · [Accepted submission](https://leetcode.com/submissions/detail/2040539355/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 44 / 44 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 21, 2026 09:46**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Binary search the slope between mid and mid+1. If it rises, the peak must lie strictly to the right; otherwise the peak is at mid or to its left. Keep that invariant until both bounds identify the same peak index.

## Complexity

- Time: O(log n), where n is array length.
- Auxiliary space / ownership: O(1) auxiliary storage.

## Assumptions and review notes

Assumes a valid mountain array with a single strict peak and the problem's minimum length. It does not validate that shape; a malformed or empty input may produce a meaningless index. Exercise peaks near both allowed ends.

- Valid-mountain and nonempty input preconditions

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
