# 1929 — Concatenation of Array

[Problem](https://leetcode.com/problems/concatenation-of-array/) · [Accepted submission](https://leetcode.com/submissions/detail/2031672202/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 92 / 92 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 13, 2026 16:05**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Allocate a result with room for twice the input length. Copy each input value into its corresponding position in both halves of that result. The result's first and second n-element segments each reproduce the original array.

## Complexity

- Time: O(n), where n=numsSize
- Auxiliary space / ownership: O(1) auxiliary state plus O(n) returned storage

## How this solution compares

**Conclusion:** Same or worse against this comparator.

**Named baseline:** Two simple copy loops for the two output halves. Allocate 2n output slots, copy nums into the first half, then into the second.

- Baseline time: O(n). Space: O(1) auxiliary plus O(n) output.
- Submitted approach: One loop writing both output halves. Time: O(n), where n=numsSize. Space: O(1) auxiliary state plus O(n) returned storage.

**How much, by analysis:** Both methods perform exactly 2n output writes and read the n source values as needed. The archive has n loop iterations rather than two n-iteration loops, but compiler optimization and memory behavior decide whether that matters. No speed or memory improvement is established.

**Why:** Combining the two loops changes control structure, not the amount of array data that must be produced.

**Trade-offs and conditions:** The one-loop version is compact; both allocate the same-sized result. Size arithmetic and allocation success are assumed.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2031672202/) displayed the following at capture on **2026-11-02T13:44:02.914Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **15.02 MB**; reported memory `Beats`: **50.05%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

The caller owns the newly allocated result and must free it. The source assumes allocation succeeds and that twice the length and allocation-size arithmetic fit the judged input bounds.

- Unchecked result malloc.
- No overflow checks for numsSize*2 outside the bounded problem domain.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
