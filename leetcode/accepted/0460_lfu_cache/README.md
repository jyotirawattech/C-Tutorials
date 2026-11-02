# 0460 — LFU Cache

[Problem](https://leetcode.com/problems/lfu-cache/) · [Accepted submission](https://leetcode.com/submissions/detail/2029340112/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 25 / 25 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 11, 2026 11:21**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Use direct key lookup and a doubly linked recency list for each frequency. Access moves a node from frequency f to f+1, while a tracked minimum frequency identifies the eviction list. Eviction removes that list's least recently used node, resolving equal-frequency ties by recency.

## Complexity

- Time: O(1) get/put within the fixed key/frequency domains; initialization zeroes O(K+F) table slots. List creation and node moves are constant-time operations.
- Auxiliary space / ownership: O(K + F + c + b), for K=100005 key slots, F=200005 frequency slots, c cached nodes and b allocated frequency lists; empty lists are retained.

## Assumptions and review notes

The submitted lFUCacheFree frees only the outer object, leaving cached nodes and frequency-list/sentinel allocations unreleased. Direct indexing assumes valid keys and frequency counts within the fixed domains; allocations are unchecked. Capacity zero is handled explicitly.

- Known incomplete teardown leaks nodes/lists/sentinels
- Fixed direct-index key and frequency domains
- Unchecked malloc/calloc results

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
