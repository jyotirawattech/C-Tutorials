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

## Assumptions and review notes

Mutates the input and assumes a nonempty rectangular grid no larger than 10x10. The queue has no overflow check outside that bound. No-fresh-orange input returns zero; disconnected fresh cells yield -1. The source's zero-latency commentary is not a performance guarantee.

- Fixed queue capacity
- In-place grid mutation
- Unmeasured latency commentary

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
