# 1046 — Last Stone Weight

[Problem](https://leetcode.com/problems/last-stone-weight/) · [Accepted submission](https://leetcode.com/submissions/detail/2033567278/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 74 / 74 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 15, 2026 12:07**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Turn the input array into a max-heap, so its root always holds the heaviest remaining stone. Repeatedly remove the two largest stones and insert their difference only when their weights differ. Restoring the heap after each removal/insertion preserves the next-heaviest selection.

## Complexity

- Time: O(n log n), including O(n) initial heap construction and O(n) heap-operation rounds.
- Auxiliary space / ownership: O(log n) auxiliary recursion depth in heapify_down; the heap reuses the input array.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Resort stones before every smash. Sort the remaining stones each round to find the two largest.

- Baseline time: O(n^2 log n) conservative worst-case bound over shrinking rounds. Space: Sort-implementation-dependent workspace.
- Submitted approach: Reusable max-heap. Time: O(n log n), with O(n) heap build. Space: O(log n) recursive heapify stack; input-backed heap.

**How much, by analysis:** There are at most n-1 smash rounds; each archive round performs two pops and at most one push with logarithmic repair, rather than one whole-array sort. No elapsed-time multiplier is established.

**Why:** The heap repairs only paths affected by two removals and an optional insertion instead of fully sorting again.

**Trade-offs and conditions:** Input order/content is changed, heap helpers assume valid sizes, and heap overhead may not help tiny stone sets. No claim over every alternative priority queue is made.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2033567278/) displayed the following at capture on **2026-11-02T13:41:58.615Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **8.72 MB**; reported memory `Beats`: **9.20%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Reorders and overwrites the input. Heap helpers assume their callers provide valid indices and nonempty pop operations; exercise a single stone, equal pairs and a chain of unequal reductions.

- In-place mutation
- Recursive heap helper uses stack space

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
