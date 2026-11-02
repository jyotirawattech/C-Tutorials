# 1200 — Minimum Absolute Difference

[Problem](https://leetcode.com/problems/minimum-absolute-difference/) · [Accepted submission](https://leetcode.com/submissions/detail/2040527387/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 39 / 39 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 21, 2026 09:30**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Sort the values so a closest pair must be adjacent. A first pass finds the smallest adjacent difference and counts its occurrences; a second pass allocates and fills exactly those pairs. Relational comparisons in the sort comparator avoid subtraction overflow there.

## Complexity

- Time: O(n log n) under the usual qsort model, plus O(n) scans; qsort's implementation is not prescribed by the C standard.
- Auxiliary space / ownership: O(k) returned pairs/metadata for k matches, plus implementation-dependent qsort workspace.

## Assumptions and review notes

Mutates the array order and assumes at least two values. Difference calculations still use int subtraction and require the platform's bounded values even though the comparator itself is overflow-safe. Allocations are unchecked; the caller must free every row and both metadata arrays.

- Unchecked allocations
- In-place sorting
- Adjacent-difference overflow outside constrained domain

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
