# 0033 — Search in Rotated Sorted Array

[Problem](https://leetcode.com/problems/search-in-rotated-sorted-array/) · [Accepted submission](https://leetcode.com/submissions/detail/2040565062/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 196 / 196 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 21, 2026 10:20**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Binary search while using the rotation's structure to identify a sorted half on every step. Check whether the target lies inside that half's value bounds, then retain that half or discard it. With distinct values, the remaining interval continues to contain the target if it exists.

## Complexity

- Time: O(log n), where n=numsSize
- Auxiliary space / ownership: O(1) auxiliary space

## Assumptions and review notes

This logic assumes a rotation of a sorted array with distinct values. Duplicates can make the sorted-half decision ambiguous; this is not the separate duplicate-tolerant rotated-search problem.

- No allocation or dangerous library call observed.
- Midpoint arithmetic is bounded by valid indices; hardware-specific performance comments are not independently established.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
