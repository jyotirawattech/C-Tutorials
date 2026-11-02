# 1354 — Construct Target Array With Multiple Sums

[Problem](https://leetcode.com/problems/construct-target-array-with-multiple-sums/) · [Accepted submission](https://leetcode.com/submissions/detail/2033686478/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 72 / 72 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 15, 2026 14:00**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Work backward from the target while maintaining a max-heap and the total sum. The largest value must have been produced using the sum of the remaining values; replacing it with its remainder skips repeated reverse subtractions. Reject impossible zero/nonpositive progress cases, and accept when the remaining sum is one or all heap values reach one.

## Complexity

- Time: O(n + r log n), where n is target length and r is the number of reverse modulo-reduction iterations.
- Auxiliary space / ownership: O(n) heap storage and O(log n) recursive heapify stack.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Reverse one construction step at a time. Use the current maximum and subtract the sum of other entries once per reverse step, restoring the heap each time.

- Baseline time: O(n+s log n), for s individual reverse steps. Space: O(n) heap.
- Submitted approach: Modulo-batched reverse max-heap. Time: O(n+r log n), for r modulo-reduction iterations. Space: O(n) heap and O(log n) recursive heapify stack.

**How much, by analysis:** Replacing x by x%rest can skip many individual x-=rest reverse steps before another element becomes maximal. The number skipped depends on the current values; no fixed improvement factor or measured runtime ratio is asserted.

**Why:** When the other entries stay fixed, a remainder operation compresses repeated subtractions of their sum; rest==1 is resolved immediately.

**Trade-offs and conditions:** Benefits depend on the target values. The source assumes positive nonempty input, bounded long long sums and successful heap allocation; arithmetic shortcuts do not replace those preconditions.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2033686478/) displayed the following at capture on **2026-11-02T13:40:27.891Z**:

- Runtime: **1 ms**; reported runtime `Beats`: **64.29%**.
- Memory: **14.38 MB**; reported memory `Beats`: **55.71%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Assumes a nonempty positive target and a sum representable by long long. The heap allocation is not checked; a zero-length target would access heap[0]. Exercise one-element targets and cases where the maximum is a multiple of the remaining sum.

- Unchecked malloc result
- Nonempty positive input precondition
- Total sum relies on problem integer bounds

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
