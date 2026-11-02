# 0084 — Largest Rectangle in Histogram

[Problem](https://leetcode.com/problems/largest-rectangle-in-histogram/) · [Accepted submission](https://leetcode.com/submissions/detail/2033033041/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 99 / 99 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 14, 2026 22:14**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Keep indices in a stack whose heights are nondecreasing. When a shorter bar arrives, pop each taller bar and compute the largest rectangle for which that bar is the limiting height, using the next smaller bar on each side. A final zero-height sentinel flushes the remaining bars; every index is pushed and popped at most once.

## Complexity

- Time: O(n), where n is the number of bars.
- Auxiliary space / ownership: O(n) auxiliary stack.

## Assumptions and review notes

Assumes nonnegative heights and a maximum area representable by int. The allocated stack is not checked for allocation failure; exercise increasing, decreasing, equal-height and empty histograms.

- Unchecked malloc result
- Height-times-width uses int; bounds depend on problem constraints

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
