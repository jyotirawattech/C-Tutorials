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

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Linear-search LRU list. Scan cached nodes for each key, then move a found node or evict the oldest.

- Baseline time: O(c) get/put for c cached items. Space: O(c).
- Submitted approach: Direct key lookup plus recency list. Time: O(1) get/put; O(K) initialization, K=10005. Space: O(K+c).

**How much, by analysis:** A baseline lookup can inspect c nodes; the archive uses one direct table access and a bounded number of pointer updates. It additionally initializes 10005 table slots; no elapsed-time speedup is measured.

**Why:** The key table removes the lookup scan, while doubly linked nodes support constant-time recency moves and eviction.

**Trade-offs and conditions:** Keys must fit the fixed domain, and table memory/init cost may be wasteful for sparse or tiny caches. Allocations and key bounds are unchecked.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2046774028/) displayed the following at capture on **2026-11-02T13:48:20.711Z**:

- Runtime: **66 ms**; reported runtime `Beats`: **12.01%**.
- Memory: **115.91 MB**; reported memory `Beats`: **5.90%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Requires keys inside the direct table's domain and successful allocations. It is single-threaded and offers no synchronization. Capacity zero immediately evicts a new entry; exercise overwrite, recency changes and eviction after a read.

- Fixed key-domain indexing
- Unchecked malloc/calloc results

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
