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

## Assumptions and review notes

Reorders the input row pointers and overwrites interval endpoints. The comparator subtracts two int starts and can overflow outside the problem's bounded domain; compare with relational operators in a hardened adaptation. Zero intervals leaves returnColumnSizes unspecified, and allocations are unchecked.

- Comparator subtraction depends on bounded inputs
- In-place input mutation
- Unchecked allocations
- Cache/zero-fragmentation comments are unmeasured

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
