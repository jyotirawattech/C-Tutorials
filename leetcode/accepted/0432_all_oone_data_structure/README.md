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

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Key-count table with min/max scan. Update counts in a hash map and scan all keys for each extreme-count query.

- Baseline time: Expected O(l) updates and O(k) min/max scan for k bounded-length keys. Space: O(k) plus hash-table storage.
- Submitted approach: Ordered count buckets plus key hash. Time: Expected O(l) inc/dec; worst O(k*l) hash search; O(1) min/max lookup. Space: O(H+k+b), H=100003 and b frequency buckets.

**How much, by analysis:** A min/max query avoids scanning k keys and reads a bounded number of links. This benefit is conditional on successful state maintenance and bounded keys, not an elapsed speedup claim.

**Why:** Adjacent count buckets maintain the ordering incrementally so extreme queries read the first or last live bucket.

**Trade-offs and conditions:** Extra bucket/list complexity and a fixed key buffer replace simple scans. The archived destructor leaks remaining keys/interior buckets, and strcpy depends on the key-length constraint; overall implementation quality is not superior merely because queries are faster in the work model.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2029540776/) displayed the following at capture on **2026-11-02T13:45:27.462Z**:

- Runtime: **31 ms**; reported runtime `Beats`: **91.43%**.
- Memory: **62.88 MB**; reported memory `Beats`: **87.68%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

The submitted allOneFree does not traverse remaining key nodes or interior frequency buckets, so populated objects leak allocations during teardown. strcpy writes into a 12-byte key buffer without checking length and depends on the platform key-length bound; a hardened variant should validate length and copy with an explicit bound.

- Known incomplete teardown leaks live keys and interior buckets
- Unchecked strcpy into fixed key buffer
- Unchecked malloc/calloc results

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
