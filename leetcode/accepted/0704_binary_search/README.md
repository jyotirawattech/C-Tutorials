# 0704 — Binary Search

[Problem](https://leetcode.com/problems/binary-search/) · [Accepted submission](https://leetcode.com/submissions/detail/2040540292/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 47 / 47 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 21, 2026 09:47**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Maintain an inclusive interval that still could contain the target. Compare the midpoint and discard the half whose sorted values cannot match, retaining the midpoint only when it is the answer. Return -1 when the interval becomes empty.

## Complexity

- Time: O(log n) for a sorted array of length n.
- Auxiliary space / ownership: O(1) auxiliary storage.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Sequential target search. Inspect sorted entries from the beginning until finding or passing the target.

- Baseline time: O(n). Space: O(1).
- Submitted approach: Inclusive-bound binary search. Time: O(log n). Space: O(1).

**How much, by analysis:** For n>=1, binary search performs at most floor(log2(n))+1 loop iterations versus up to n inspected entries in sequential search. For n=1024 that is at most 11 iterations versus 1024 entries; these different operations are not a measured speed ratio.

**Why:** Sorted order lets each midpoint comparison discard roughly half of the remaining candidates.

**Trade-offs and conditions:** Requires random-access sorted data. A small or cache-friendly sequential search may still be faster on a particular host; duplicate targets need not return the first position.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2040540292/) displayed the following at capture on **2026-11-02T13:50:08.694Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **9.95 MB**; reported memory `Beats`: **69.59%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Requires ascending sorted input; with duplicates it returns a matching position rather than necessarily the first. The midpoint formula avoids adding two potentially large indices. Exercise an absent target, endpoint hits and empty input.

- Sorted-input precondition

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
