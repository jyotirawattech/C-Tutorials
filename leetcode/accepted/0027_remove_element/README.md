# 0027 — Remove Element

[Problem](https://leetcode.com/problems/remove-element/) · [Accepted submission](https://leetcode.com/submissions/detail/2033798016/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 116 / 116 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 15, 2026 15:41**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Scan with a read index and keep a write index for retained values. Copy each value unequal to val into the next retained slot, then advance the write index. The processed output prefix always contains exactly the retained processed elements in their original order.

## Complexity

- Time: O(n), where n=numsSize
- Auxiliary space / ownership: O(1) auxiliary space; input is modified

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Delete each matching value by shifting its suffix. When val is found, move every later element one slot left and continue.

- Baseline time: O(n^2) worst case. Space: O(1) auxiliary.
- Submitted approach: Stable read/write compaction. Time: O(n), where n=numsSize. Space: O(1) auxiliary space; input is modified.

**How much, by analysis:** Repeated deletion can move n(n-1)/2 elements when all values are removed. Compaction performs n value tests and at most n retained-element writes; for that all-removed case it performs zero writes. These are element-operation counts, not a stopwatch speedup.

**Why:** A write cursor retains useful elements directly, avoiding repeated movement of the same suffix.

**Trade-offs and conditions:** Both modify the array. The returned length defines the useful prefix; trailing values are not cleared or deallocated.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2033798016/) displayed the following at capture on **2026-11-02T13:51:39.971Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **10.41 MB**; reported memory `Beats`: **20.75%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Only the first returned-count elements are meaningful after compaction. The tail is not cleared and the allocation is not resized; callers must use the returned logical length.

- No allocation or dangerous library call observed.
- A readable/writable nums buffer of numsSize elements is assumed.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
