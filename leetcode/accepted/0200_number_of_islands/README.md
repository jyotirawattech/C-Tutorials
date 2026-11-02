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

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** DFS with separate visited grid. Flood-fill each unvisited land component using an explicit visited matrix.

- Baseline time: O(m*n). Space: O(m*n) visited storage and worst-case traversal stack.
- Submitted approach: Recursive sink-in-place DFS. Time: O(m*n). Space: O(m*n) worst-case recursive stack; no visited matrix.

**How much, by analysis:** One m-by-n visited matrix is avoided, but worst-case auxiliary growth remains O(m*n) because recursion can reach every land cell. No asymptotic total-space or elapsed-time superiority is established.

**Why:** Changing visited land to water removes the separate visited grid while preserving once-per-cell exploration.

**Trade-offs and conditions:** The input map is destroyed, and a large connected island can exhaust the stack. An iterative traversal can provide better stack control.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2046776629/) displayed the following at capture on **2026-11-02T13:48:09.280Z**:

- Runtime: **20 ms**; reported runtime `Beats`: **64.03%**.
- Memory: **12.32 MB**; reported memory `Beats`: **58.33%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Destroys the input land map and assumes a rectangular grid using gridColSize[0] for every row. A large connected island can create deep recursion and exhaust the call stack; an iterative stack would be a separate adaptation. Empty row count is handled.

- In-place grid mutation
- Potential deep recursion
- Rectangular-grid precondition

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
