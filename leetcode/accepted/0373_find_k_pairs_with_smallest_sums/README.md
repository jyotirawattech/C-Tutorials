# 0373 — Find K Pairs with Smallest Sums

[Problem](https://leetcode.com/problems/find-k-pairs-with-smallest-sums/) · [Accepted submission](https://leetcode.com/submissions/detail/2033580722/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 32 / 32 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 15, 2026 12:17**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Treat each first-array value as the start of a sorted row of pair sums with the second array. A min-heap stores one frontier pair per active row; extracting a pair advances only that row. The smallest unseen pair must remain at one of these frontiers when both inputs are sorted.

## Complexity

- Time: O((r+p) log(r+1)), where r=min(nums1Size,k) and p=min(k,nums1Size*nums2Size) returned pairs
- Auxiliary space / ownership: O(r) auxiliary heap; O(p) returned pair storage and column sizes

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Materialize and sort every cross-array pair. Create all m*n pairs, sort by sum, and take the first p.

- Baseline time: O(m*n log(m*n)) with comparison sorting. Space: O(m*n) pair table plus returned p pairs.
- Submitted approach: Min-heap of sorted-row frontiers. Time: O((r+p) log(r+1)), where r=min(nums1Size,k) and p=min(k,nums1Size*nums2Size) returned pairs. Space: O(r) auxiliary heap; O(p) returned pair storage and column sizes.

**How much, by analysis:** The baseline materializes m*n pairs. This source retains r=min(m,k) heap frontiers and performs p=min(k,m*n) output-extraction cycles, each with at most a pop and next-row push. This is a storage/frontier-work comparison; no measured runtime factor is claimed.

**Why:** Sorted inputs let the algorithm expand only the next candidate from each active row instead of storing the complete Cartesian product.

**Trade-offs and conditions:** Requires sorted nonempty arrays and more involved heap/ownership code. Allocation failures are unchecked; returned rows, outer pointers and column-size storage all need caller cleanup.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2033580722/) displayed the following at capture on **2026-11-02T13:41:54.947Z**:

- Runtime: **25 ms**; reported runtime `Beats`: **49.23%**.
- Memory: **61.18 MB**; reported memory `Beats`: **65.38%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Both arrays must be nonempty and sorted. The caller must free each returned pair, the result pointer array, and the separate column-size array; allocation failures are not handled in the archived source.

- Unchecked heap/result/row allocations.
- Pair sums use int and depend on the problem's bounded numeric domain; no arbitrary-integer safety claim.
- The source's 'HARDWARE FIX' comment describes widened C multiplication but does not establish register choice or a hardware optimization.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
