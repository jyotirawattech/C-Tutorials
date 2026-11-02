# 0146 — LRU Cache

[Problem](https://leetcode.com/problems/lru-cache/) · [Accepted submission](https://leetcode.com/submissions/detail/2046774028/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 25 / 25 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 26, 2026 17:15**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Use a direct key-to-node table for lookup and a doubly linked list for recency order. Reads and updates move a node to the most-recent end; inserting beyond capacity removes the node next to the least-recent sentinel. Teardown walks and frees the complete list, including both sentinels.

## Complexity

- Time: O(1) get/put within the fixed key domain, O(K) creation for K=10005 table slots, and O(c) teardown for c cached nodes.
- Auxiliary space / ownership: O(K+c), for the direct key table and cached nodes.

## Assumptions and review notes

Requires keys inside the direct table's domain and successful allocations. It is single-threaded and offers no synchronization. Capacity zero immediately evicts a new entry; exercise overwrite, recency changes and eviction after a read.

- Fixed key-domain indexing
- Unchecked malloc/calloc results

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
