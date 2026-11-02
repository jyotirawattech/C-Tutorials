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

## Assumptions and review notes

Borrows the caller's matrix instead of copying it, so that matrix must stay alive and unchanged. The history has no capacity check beyond the platform's at-most-500-operation bound; rectangle/query bounds and allocations are unchecked.

- Fixed update-history capacity
- Borrowed matrix lifetime requirement
- Unchecked malloc results

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
