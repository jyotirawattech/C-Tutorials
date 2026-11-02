# 1470 — Shuffle the Array

[Problem](https://leetcode.com/problems/shuffle-the-array/) · [Accepted submission](https://leetcode.com/submissions/detail/2032914942/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 53 / 53 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 14, 2026 20:09**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Keep one read pointer at the start of each half of the input. Append one value from the first half and one from the second half into a newly allocated result for each iteration. The write pointer always follows the completed interleaved prefix.

## Complexity

- Time: O(n), where the input contains 2n elements.
- Auxiliary space / ownership: O(1) auxiliary work space, plus O(n) returned output.

## How this solution compares

**Conclusion:** Improvement not established.

**Named baseline:** Indexed interleave into output. Write nums[i] to output[2*i] and nums[n+i] to output[2*i+1].

- Baseline time: O(n). Space: O(1) auxiliary state plus O(n) output.
- Submitted approach: Pointer-cursor interleave. Time: O(n). Space: O(1) auxiliary pointers plus O(n) output.

**How much, by analysis:** Both read and write exactly 2n elements. Pointer syntax does not establish fewer compiled instructions or lower runtime; no advantage is measured.

**Why:** The pointer version expresses the same two reads and two writes per pair as the indexed baseline.

**Trade-offs and conditions:** Requires numsSize==2*n, valid lengths and successful output allocation. Readability preferences and compiler optimization determine any constant-level differences.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2032914942/) displayed the following at capture on **2026-11-02T13:44:06.267Z**:

- Runtime: **12 ms**; reported runtime `Beats`: **73.68%**.
- Memory: **12.35 MB**; reported memory `Beats`: **25.73%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Requires numsSize == 2*n and valid input pointers. A mismatched n can read or write beyond the arrays; the output allocation is unchecked and must be freed by the caller.

- Unchecked malloc result
- Pointer bounds depend on equal-half input contract

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
