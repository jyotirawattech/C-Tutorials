# 2144 — Minimum Cost of Buying Candies With Discount

[Problem](https://leetcode.com/problems/minimum-cost-of-buying-candies-with-discount/) · [Accepted submission](https://leetcode.com/submissions/detail/2046771410/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 192 / 192 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 26, 2026 17:12**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Count candy prices in a bounded frequency array and visit prices in descending order. Pay for two candies, then take the next candy free, repeating that three-item cycle. Processing larger prices first ensures the free item never exceeds either paid item and maximizes the useful discount.

## Complexity

- Time: O(n+V), for n candies and the fixed price domain V=100.
- Auxiliary space / ownership: O(V) frequency storage, constant for the implemented domain.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Sort prices descending and skip every third. Use comparison sorting, then pay for the first two candies in each group of three.

- Baseline time: O(n log n) with a comparison sort. Space: Sort-dependent workspace.
- Submitted approach: Bounded price-frequency sweep. Time: O(n+V), V=100. Space: O(V).

**How much, by analysis:** The archive counts n prices, visits 100 price bins and consumes n counted candies. This replaces comparison-sort growth with n+100 domain work, not a measured runtime percentage.

**Why:** The known 1..100 price domain replaces comparison sorting with counts and descending enumeration.

**Trade-offs and conditions:** Requires the bounded price domain and safe integer totals. For small n or a wide unconstrained domain, sorting may be simpler or faster; guaranteed cache-hit comments are unsupported.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2046771410/) displayed the following at capture on **2026-11-02T13:48:25.408Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **9.27 MB**; reported memory `Beats`: **6.30%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Direct indexing assumes prices in 1..100, and the running total relies on problem integer bounds. The source's exact byte-size and guaranteed-cache-hit claims are platform-dependent or unmeasured, not benchmark evidence. Exercise one/two candies and duplicate prices across discount groups.

- Fixed price-domain indexing
- Unverified cache and platform-size commentary

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
