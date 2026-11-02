# 0088 — Merge Sorted Array

[Problem](https://leetcode.com/problems/merge-sorted-array/) · [Accepted submission](https://leetcode.com/submissions/detail/2033796939/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 59 / 59 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 15, 2026 15:40**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Read the largest remaining values from the ends of the two sorted inputs and write the larger one into the last unused destination slot. Working backward avoids overwriting unread values in nums1. When nums2 is exhausted, any remaining nums1 prefix is already in place.

## Complexity

- Time: O(m+n), for m initial nums1 values and n nums2 values.
- Auxiliary space / ownership: O(1) auxiliary storage.

## Assumptions and review notes

Requires sorted inputs, destination capacity at least m+n, and a nums2 source not improperly overlapping the destination. The function ignores the supplied capacity parameters and trusts m/n. Exercise an empty first logical array and a second array whose values all precede the first.

- Unchecked caller-provided lengths/capacity
- In-place destination mutation

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
