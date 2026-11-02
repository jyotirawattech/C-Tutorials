# 0912 — Sort an Array

[Problem](https://leetcode.com/problems/sort-an-array/) · [Accepted submission](https://leetcode.com/submissions/detail/2040536510/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 21 / 21 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 21, 2026 09:42**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Build a max-heap in the input array, then repeatedly swap its root into the last active position. Restore the reduced heap with an iterative sift-down after every extraction. The suffix is sorted while the prefix remains a valid heap.

## Complexity

- Time: O(n log n) worst case, with O(n) initial heap construction.
- Auxiliary space / ownership: O(1) auxiliary storage because sift-down is iterative and sorting is in place.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Insertion sort. Insert each next element into its sorted prefix by shifting larger predecessors.

- Baseline time: O(n^2) worst case; O(n) for already sorted input. Space: O(1).
- Submitted approach: Iterative in-place heapsort. Time: O(n log n) worst case; O(n) heap build. Space: O(1).

**How much, by analysis:** Reverse-order insertion sort can shift n(n-1)/2 elements. The archive does n-1 heap extractions, each with O(log n) sift-down work. No elapsed speed multiplier is derived from these bounds.

**Why:** Heap extraction limits each repositioning to a root-to-leaf path rather than moving a whole prefix.

**Trade-offs and conditions:** Insertion sort can win for small or nearly sorted input and is stable; heapsort is unstable and returns the mutated input pointer. No claim of superiority over every O(n log n) sort is made.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2040536510/) displayed the following at capture on **2026-11-02T13:50:19.074Z**:

- Runtime: **58 ms**; reported runtime `Beats`: **38.61%**.
- Memory: **59.26 MB**; reported memory `Beats`: **70.38%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Mutates the input and returns the same pointer, so callers must not treat it as an independently allocated output. Heapsort is not stable. Index arithmetic assumes problem-bounded sizes; exercise duplicates, reverse order and one-element arrays.

- Input-backed returned pointer
- In-place unstable sorting
- Heap index arithmetic relies on size bounds

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
