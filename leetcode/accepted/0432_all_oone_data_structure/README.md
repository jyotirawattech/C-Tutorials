# 0432 — All O`one Data Structure

[Problem](https://leetcode.com/problems/all-oone-data-structure/) · [Accepted submission](https://leetcode.com/submissions/detail/2029540776/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 25 / 25 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 11, 2026 14:39**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Map each key to a node in an ordered doubly linked list of frequency buckets. Incrementing or decrementing moves the node to an adjacent count bucket, creating that bucket if needed and deleting empty buckets. The first and last non-sentinel buckets expose minimum and maximum keys directly.

## Complexity

- Time: Expected O(l) inc/dec for key length l and well-distributed hashes, O(k*l) worst-case collision search among k keys, and O(1) min/max lookup. Key length is bounded by the problem constraints.
- Auxiliary space / ownership: O(H + k + b), for H=100003 bucket pointers, k key nodes and b frequency buckets.

## Assumptions and review notes

The submitted allOneFree does not traverse remaining key nodes or interior frequency buckets, so populated objects leak allocations during teardown. strcpy writes into a 12-byte key buffer without checking length and depends on the platform key-length bound; a hardened variant should validate length and copy with an explicit bound.

- Known incomplete teardown leaks live keys and interior buckets
- Unchecked strcpy into fixed key buffer
- Unchecked malloc/calloc results

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
