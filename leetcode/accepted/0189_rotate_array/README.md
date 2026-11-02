# 0189 — Rotate Array

[Problem](https://leetcode.com/problems/rotate-array/) · [Accepted submission](https://leetcode.com/submissions/detail/463974219/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 35 / 35 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Mar 06, 2021 01:20**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Reduce the requested rotation count modulo the array length. Perform that many one-position right rotations by saving the first value, moving the last value to the front, shifting the interior, and restoring the saved value into index one. Each completed pass preserves the array's elements while changing their positions by one.

## Complexity

- Time: O(n*(k mod n)), where n=numsSize; worst case O(n^2)
- Auxiliary space / ownership: O(1) auxiliary space; input is modified

## How this solution compares

**Conclusion:** Same or worse against this comparator.

**Named baseline:** Three-reversal array rotation. Reverse the whole array, then reverse each of the two rotation segments.

- Baseline time: O(n). Space: O(1).
- Submitted approach: Repeated one-position right shifts. Time: O(n*(k mod n)), where n=numsSize; worst case O(n^2). Space: O(1) auxiliary space; input is modified.

**How much, by analysis:** For n>1 and 1<=r=k mod n<n, the archived source makes n*r array writes. Three reversals perform floor(n/2)+floor(r/2)+floor((n-r)/2) swaps, at most n swaps or 2n array writes. Both can return immediately when r=0. This is a write-count model; it is not a runtime ratio. A small r can favor simple shifts, while r growing with n gives quadratic work.

**Why:** The archive saves space, but its repeated shifts revisit every element for each residual rotation; it is not the linear three-reversal algorithm.

**Trade-offs and conditions:** Both mutate the array and use constant extra state. The archive is simple but has no overall time-complexity advantage over reversal.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/463974219/) displayed the following at capture on **2026-11-02T13:46:13.936Z**:

- Runtime: **540 ms**; reported runtime `Beats`: **6.23%**.
- Memory: **7.88 MB**; reported memory `Beats`: **100.00%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

This is a repeated-shift implementation, not the O(n) three-reversal method. It mutates the caller's array and assumes nonnegative k; zero length is handled before modulo.

- No allocation or dangerous library call observed.
- No new performance measurement is established; large n and k mod n incur repeated full-array shifts.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
