# 0493 — Reverse Pairs

[Problem](https://leetcode.com/problems/reverse-pairs/) · [Accepted submission](https://leetcode.com/submissions/detail/2041566308/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 140 / 140 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 22, 2026 09:22**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Recursively sort each half while counting its internal reverse pairs. Since both halves are sorted, advance a right-half pointer monotonically to count cross pairs satisfying left > 2*right, then merge. Widening the comparison to long long avoids overflowing the doubled input value within the judged integer domain.

## Complexity

- Time: O(n log n), where n=numsSize
- Auxiliary space / ownership: O(n) shared temporary array plus O(log n) recursion depth

## Assumptions and review notes

The function sorts and mutates its input. A failed temporary allocation returns zero instead of a distinct error, and the int result relies on the problem's input-length bound.

- Allocation failure is checked but conflated with a valid zero pair count.
- Merge storage is O(n), despite a source comment using 'in-place' terminology.
- The source's fragmentation/latency claims are not supported by benchmarks.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
