# 0352 — Data Stream as Disjoint Intervals

[Problem](https://leetcode.com/problems/data-stream-as-disjoint-intervals/) · [Accepted submission](https://leetcode.com/submissions/detail/2029363865/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 8 / 8 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 11, 2026 11:41**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Track which values have appeared and use disjoint-set parent links whose root is the highest value in each contiguous group. Adding a new value joins any adjacent groups, while path compression shortens future parent walks. Enumerating values emits each interval from its first seen value to its root and skips directly to that endpoint.

## Complexity

- Time: Create O(V); an add can take O(V) in the worst case because unions do not use rank; interval enumeration O(V), where V is the fixed value-domain bound.
- Auxiliary space / ownership: O(V) persistent parent/seen arrays, O(V) result pointer/size buffers, and up to O(V) recursive find depth in the worst case.

## How this solution compares

**Conclusion:** Same or worse against this comparator.

**Named baseline:** Presence array and complete domain scan. Mark each value and scan the bounded domain to emit maximal seen runs.

- Baseline time: O(1) add and O(V) enumeration. Space: O(V) presence flags plus output.
- Submitted approach: Presence flags plus endpoint-parent links. Time: Worst O(V) add without rank balancing; O(V) enumeration; O(V) create. Space: O(V) flags/parents, output buffers and possible recursive find depth.

**How much, by analysis:** Both reserve domain-sized arrays and have an O(V) enumeration bound. The archive adds V parent integers and can traverse a long parent chain on insertion; no proven general improvement is established.

**Why:** Endpoint links can skip contiguous runs during enumeration, but their traversal/maintenance adds work and does not improve the stated worst-case bounds over this bounded-domain baseline.

**Trade-offs and conditions:** May reduce some enumeration loop steps after compression, but adds recursive depth, allocations and a fixed 0..10000 domain. An ordered interval map is another baseline with different trade-offs.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2029363865/) displayed the following at capture on **2026-11-02T13:45:38.584Z**:

- Runtime: **7 ms**; reported runtime `Beats`: **6.67%**.
- Memory: **17.30 MB**; reported memory `Beats`: **7.62%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Assumes values lie in 0..10000 and relies on fixed arrays and unchecked allocations. Each returned row, the row-pointer array and column-size array belong to the caller. Long parent chains can create substantial recursion before compression.

- Fixed value-domain indexing
- Unchecked allocation results
- Recursive find without rank balancing

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
