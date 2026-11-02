# 0215 — Kth Largest Element in an Array

[Problem](https://leetcode.com/problems/kth-largest-element-in-an-array/) · [Accepted submission](https://leetcode.com/submissions/detail/2040535241/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 46 / 46 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 21, 2026 09:40**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Choose a pivot and partition the active interval into values below, equal to and above it. Convert kth-largest selection to the zero-based index n-k, then recurse only into the partition containing that index. A large equal-value block can finish selection without recursing through each duplicate.

## Complexity

- Time: Expected O(n) with suitable random pivot behavior; O(n^2) worst case
- Auxiliary space / ownership: In-place partitioning with expected O(log n) recursive depth and O(n) worst-case recursive depth

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Sort the whole array then select n-k. Use a comparison sort and read the requested rank from the result.

- Baseline time: O(n log n) for a sort with that guarantee. Space: Implementation-dependent sorting workspace.
- Submitted approach: Random-pivot three-way quickselect. Time: Expected O(n) with suitable random pivot behavior; O(n^2) worst case. Space: In-place partitioning with expected O(log n) recursive depth and O(n) worst-case recursive depth.

**How much, by analysis:** Expected partition work is O(n) under suitable pivot behavior, against O(n log n) sorting growth. Repeated extreme pivots can instead produce quadratic work. No fixed speed factor follows from those bounds or from the source's rand/time calls.

**Why:** Partitioning needs only the rank-containing side; it avoids fully ordering values irrelevant to the chosen rank and groups duplicate pivots together.

**Trade-offs and conditions:** Mutates input, reseeds global libc randomness, and has a linear recursion-depth worst case. A guaranteed O(n log n) sort offers a stronger worst-case bound and leaves all ranks ordered.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2040535241/) displayed the following at capture on **2026-11-02T13:50:22.381Z**:

- Runtime: **4 ms**; reported runtime `Beats`: **87.00%**.
- Memory: **15.27 MB**; reported memory `Beats`: **83.28%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

The input is mutated, k must be in 1..n, and srand(time(NULL)) reseeds shared libc random state on every call. The random source is not cryptographic and does not provide a worst-case time or recursion bound.

- Uses libc rand/srand/time; unsuitable as security randomness and changes process-wide random state.
- No range checks for invalid k/empty input.
- Worst-case recursion may be linear; source 'hardened' commentary does not establish a robustness guarantee.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
