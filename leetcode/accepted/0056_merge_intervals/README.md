# 0056 — Merge Intervals

[Problem](https://leetcode.com/problems/merge-intervals/) · [Accepted submission](https://leetcode.com/submissions/detail/2046774188/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 172 / 172 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 26, 2026 17:15**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Sort intervals by start value, then maintain a compacted prefix of disjoint merged intervals. Extend the last output interval when the next interval overlaps; otherwise advance the output slot and copy the new interval there. Finally allocate independent result rows from the compacted prefix.

## Complexity

- Time: O(n log n) under the usual qsort complexity model, followed by an O(n) sweep and output copy; the C standard does not guarantee qsort's algorithmic bound.
- Auxiliary space / ownership: O(k) returned rows and metadata for k merged intervals, plus implementation-dependent qsort workspace.

## How this solution compares

**Conclusion:** Same or worse against this comparator.

**Named baseline:** Sort and merge directly into output. Sort by interval start and append or extend disjoint result rows during one sweep.

- Baseline time: Usually O(n log n) with an O(n) sweep. Space: O(k) returned rows plus sort workspace for k merged intervals.
- Submitted approach: Sort, compact input, then allocate output. Time: Usually O(n log n), plus O(n) sweep and O(k) copy. Space: O(k) returned rows plus implementation-dependent qsort workspace.

**How much, by analysis:** Both perform one sort and one linear merge sweep; the archive additionally copies k compacted intervals into allocated output. No asymptotic or measured advantage over this baseline is established.

**Why:** Sorting makes overlap decisions local, but the archived second allocation/copy does not remove the sort or output-storage costs of this baseline.

**Trade-offs and conditions:** Input pointers/endpoints are mutated. Comparator subtraction can overflow outside the bounded problem domain, and allocations are unchecked. C does not prescribe qsort's algorithmic bound.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2046774188/) displayed the following at capture on **2026-11-02T13:48:17.219Z**:

- Runtime: **3 ms**; reported runtime `Beats`: **66.99%**.
- Memory: **18.75 MB**; reported memory `Beats`: **38.42%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Reorders the input row pointers and overwrites interval endpoints. The comparator subtracts two int starts and can overflow outside the problem's bounded domain; compare with relational operators in a hardened adaptation. Zero intervals leaves returnColumnSizes unspecified, and allocations are unchecked.

- Comparator subtraction depends on bounded inputs
- In-place input mutation
- Unchecked allocations
- Cache/zero-fragmentation comments are unmeasured

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
