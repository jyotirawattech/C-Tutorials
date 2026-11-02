# 0001 — Two Sum

[Problem](https://leetcode.com/problems/two-sum/) · [Accepted submission](https://leetcode.com/submissions/detail/2037075478/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 63 / 63 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 18, 2026 10:37**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Scan values while storing previously seen numbers and their original indices in a chained hash table. Before inserting the current number, look up target-current; a match therefore uses a different earlier array position. On success, release all hash nodes and return the two indices.

## Complexity

- Time: Expected O(n+B) with favorable hashing and O(n^2+B) worst case, where B=10007 buckets; fixed B gives the usual expected O(n) description
- Auxiliary space / ownership: O(n+B) auxiliary hash storage and a two-integer returned allocation

## Assumptions and review notes

The judged contract guarantees a solution. If no pair exists, the fallback returns uninitialized result values with returnSize still two and frees only the bucket array, leaking inserted nodes; allocations are also unchecked.

- Unchecked result, bucket-array and per-node allocations.
- No-solution fallback leaks nodes and exposes uninitialized result values outside the guaranteed-solution contract.
- target-nums[i] arithmetic assumes bounded input values; a prime bucket count does not prevent collisions.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
