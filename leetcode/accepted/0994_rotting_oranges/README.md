# 0994 — Rotting Oranges

[Problem](https://leetcode.com/problems/rotting-oranges/) · [Accepted submission](https://leetcode.com/submissions/detail/2046777765/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 307 / 307 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 26, 2026 17:19**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Start a breadth-first search from every initially rotten orange at time zero. Mark each newly reached fresh orange rotten immediately and enqueue it with its parent's time plus one, ensuring each cell is processed once. Return the last reached time only if every fresh orange became reachable; otherwise return -1.

## Complexity

- Time: O(m*n), for m rows and n columns.
- Auxiliary space / ownership: A fixed 100-element queue under the 10x10 bound; conceptually O(m*n) queue space.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Minute-by-minute full grid rescans. Scan every cell at each minute and stage newly rotten cells separately before the next minute.

- Baseline time: O(m*n*d), for d propagation rounds. Space: O(m*n) staged-state storage.
- Submitted approach: Multi-source BFS. Time: O(m*n). Space: Fixed 100-entry queue under a 10x10 bound; generally O(m*n).

**How much, by analysis:** Each grid cell enters the archived queue at most once. The baseline can inspect m*n cells during each of d minutes; this avoids a factor of repeated full scans in the work model, not a measured d-times speedup.

**Why:** The queue visits only newly reachable cells and timestamps their propagation instead of rescanning the whole grid per minute.

**Trade-offs and conditions:** The archive mutates the input and has a fixed queue capacity. d=0 or tiny grids may show little elapsed benefit; the zero-latency source comment is not a measurement.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2046777765/) displayed the following at capture on **2026-11-02T13:48:05.488Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **10.46 MB**; reported memory `Beats`: **5.61%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Mutates the input and assumes a nonempty rectangular grid no larger than 10x10. The queue has no overflow check outside that bound. No-fresh-orange input returns zero; disconnected fresh cells yield -1. The source's zero-latency commentary is not a performance guarantee.

- Fixed queue capacity
- In-place grid mutation
- Unmeasured latency commentary

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
