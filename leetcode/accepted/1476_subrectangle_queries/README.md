# 1476 — Subrectangle Queries

[Problem](https://leetcode.com/problems/subrectangle-queries/) · [Accepted submission](https://leetcode.com/submissions/detail/2029644148/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 52 / 52 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 11, 2026 16:22**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Record each update rectangle and value without rewriting the matrix. To answer a point query, scan updates from newest to oldest and return the first rectangle covering the point; if none covers it, use the original matrix value. Reverse chronological lookup ensures the most recent applicable assignment wins.

## Complexity

- Time: Create and each update are O(1); a query is O(u) for u recorded updates, and teardown is O(1).
- Auxiliary space / ownership: A fixed history of 500 updates, O(1) for the implemented bound; conceptually O(u) stored history, excluding the borrowed input matrix.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Eager rectangle writes. Rewrite every affected cell on update, then answer queries directly from the matrix.

- Baseline time: O(A) per update of area A; O(1) query. Space: Matrix storage; optional copy if preserving input.
- Submitted approach: Deferred update history. Time: O(1) append update; O(u) worst-case query after u updates. Space: Fixed 500-update history plus borrowed original matrix.

**How much, by analysis:** An update replaces A cell assignments with one five-field history append, but a query may inspect u rectangles rather than one matrix cell. Whether it is better depends on areas and the update/query mix; no universal winner is established.

**Why:** The archive shifts work from updates to queries by searching newest assignments instead of rewriting cells.

**Trade-offs and conditions:** Query-heavy workloads can be worse. The original matrix must remain alive/unchanged; the history capacity, bounds and allocations are trusted.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2029644148/) displayed the following at capture on **2026-11-02T13:44:11.501Z**:

- Runtime: **33 ms**; reported runtime `Beats`: **61.70%**.
- Memory: **16.64 MB**; reported memory `Beats`: **21.28%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Borrows the caller's matrix instead of copying it, so that matrix must stay alive and unchanged. The history has no capacity check beyond the platform's at-most-500-operation bound; rectangle/query bounds and allocations are unchecked.

- Fixed update-history capacity
- Borrowed matrix lifetime requirement
- Unchecked malloc results

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
