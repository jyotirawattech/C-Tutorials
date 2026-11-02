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

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Enumerate every histogram interval. Extend every left endpoint rightward while tracking the minimum height.

- Baseline time: O(n^2). Space: O(1).
- Submitted approach: Monotonic index stack. Time: O(n). Space: O(n).

**How much, by analysis:** The baseline examines n(n+1)/2 intervals. Each real bar enters and leaves the archived stack at most once, giving at most n pushes and n pops for those bars. These are different operation counts, not a speed multiplier.

**Why:** The next smaller height determines a popped bar's maximal width, so already resolved candidates need no rescanning.

**Trade-offs and conditions:** Linear auxiliary memory replaces the baseline's constant space. Allocation failure and int area overflow outside problem constraints are not handled.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2033033041/) displayed the following at capture on **2026-11-02T13:42:42.796Z**:

- Runtime: **15 ms**; reported runtime `Beats`: **8.25%**.
- Memory: **17.58 MB**; reported memory `Beats`: **7.90%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Assumes nonnegative heights and a maximum area representable by int. The allocated stack is not checked for allocation failure; exercise increasing, decreasing, equal-height and empty histograms.

- Unchecked malloc result
- Height-times-width uses int; bounds depend on problem constraints

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
