# 0200 — Number of Islands

[Problem](https://leetcode.com/problems/number-of-islands/) · [Accepted submission](https://leetcode.com/submissions/detail/2046776629/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 49 / 49 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 26, 2026 17:18**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Scan every grid cell and start a depth-first flood fill whenever an unvisited land cell is found. Count that start as one island and change every four-connected land cell in the component to water. This mutation prevents any component from being counted twice.

## Complexity

- Time: O(m*n), for m rows and n columns.
- Auxiliary space / ownership: O(m*n) worst-case recursive call stack; no separate visited matrix.

## Assumptions and review notes

Destroys the input land map and assumes a rectangular grid using gridColSize[0] for every row. A large connected island can create deep recursion and exhaust the call stack; an iterative stack would be a separate adaptation. Empty row count is handled.

- In-place grid mutation
- Potential deep recursion
- Rectangular-grid precondition

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
