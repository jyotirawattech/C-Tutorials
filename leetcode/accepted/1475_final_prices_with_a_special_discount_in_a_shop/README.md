# 1475 — Final Prices With a Special Discount in a Shop

[Problem](https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/) · [Accepted submission](https://leetcode.com/submissions/detail/2033027189/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 103 / 103 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 14, 2026 22:09**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Keep indices waiting for their first later price that is less than or equal to their original price. When such a price arrives, pop matching pending indices and subtract the current price directly in the input array. Remaining pending indices keep their original values because no eligible later discount was found.

## Complexity

- Time: O(n) amortized, where n=pricesSize; each index enters and leaves the stack at most once
- Auxiliary space / ownership: O(n) auxiliary stack; the returned pointer aliases the existing input array

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Search every suffix for the first eligible discount. For each price, scan later prices until the first value <= it is found.

- Baseline time: O(n^2) worst case. Space: O(1) auxiliary for an in-place baseline.
- Submitted approach: Monotonic pending-discount stack. Time: O(n) amortized, where n=pricesSize; each index enters and leaves the stack at most once. Space: O(n) auxiliary stack; the returned pointer aliases the existing input array.

**How much, by analysis:** Strictly increasing prices make the baseline perform n(n-1)/2 suffix comparisons. The archive pushes n indices and pops at most n, producing amortized linear work. These bounds do not supply a stopwatch speed factor.

**Why:** Pending indices share a forward scan, and each is resolved only once when its first qualifying price arrives.

**Trade-offs and conditions:** Adds O(n) stack memory and mutates/returns the original array, rather than allocating an independent result. The generic malloc-return comment must not be treated as an ownership guarantee.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2033027189/) displayed the following at capture on **2026-11-02T13:42:49.621Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **11.90 MB**; reported memory `Beats`: **54.81%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

The function mutates prices and returns that same pointer, despite the generic comment about a malloc-allocated return. Do not free the result separately from the input or assume an independent copy; the stack allocation is also unchecked.

- Unchecked stack malloc.
- Generic malloc-return comment is inconsistent with the actual returned input alias.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
