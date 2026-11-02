# 0207 — Course Schedule

[Problem](https://leetcode.com/problems/course-schedule/) · [Accepted submission](https://leetcode.com/submissions/detail/2049492075/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 54 / 54 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 29, 2026 08:57**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Build prerequisite-to-course adjacency lists and count each course's incoming dependencies. Kahn's topological traversal starts with zero-indegree courses and releases a neighbor when its final prerequisite is removed. All courses are finishable exactly when the traversal processes every course.

## Complexity

- Time: O(V+E), where V=numCourses and E=prerequisitesSize
- Auxiliary space / ownership: O(V+E) adjacency/indegree storage plus a fixed 2000-element queue

## Assumptions and review notes

The queue assumes at most 2000 courses and every prerequisite row has two valid course IDs. The allocation-failure early return does not free other successful allocations; the fragment also relies on judge-provided standard declarations.

- Partial-allocation failure leaks earlier successful allocations.
- No range/row-width checks for prerequisite IDs; fixed queue capacity depends on judged constraints.
- Missing standard bool/stdlib declarations in this captured fragment.
- Source 'zero latency'/'prevents heap fragmentation' comments are unsupported as universal performance claims.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
