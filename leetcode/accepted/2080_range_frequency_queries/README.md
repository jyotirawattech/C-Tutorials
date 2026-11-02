# 2080 — Range Frequency Queries

[Problem](https://leetcode.com/problems/range-frequency-queries/) · [Accepted submission](https://leetcode.com/submissions/detail/2029635919/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 20 / 20 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 11, 2026 16:13**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Build an increasing list of source indices for each possible value using two passes: first count exact capacities, then populate the lists. For a query, lower_bound finds the first index at least left and upper_bound finds the first index greater than right. Their difference counts occurrences inside the inclusive range.

## Complexity

- Time: O(n + V) construction, O(log f) per query for frequency f of the queried value, and O(n + V) total teardown; V is the 10001-entry value domain.
- Auxiliary space / ownership: O(n + V) for the index lists, pointers and counts.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Scan each queried range. Count matching values directly between left and right for every query.

- Baseline time: O(w) per query of width w; O(q*n) worst case across q queries. Space: O(1) working space while retaining input.
- Submitted approach: Per-value sorted index lists. Time: O(n+V) build; O(log(f+1)) query with O(1) handling when the value is absent, where f is its stored frequency. Space: O(n+V), V=10001.

**How much, by analysis:** A width-w query inspects w values in the baseline; the archive does two logarithmic index-list searches after preprocessing. Overall benefit depends on query count and range widths relative to the O(n+V) setup cost.

**Why:** Two binary searches locate the queried value's positions in the requested range without examining each range element.

**Trade-offs and conditions:** Uses additional stored positions and a fixed value domain. One tiny query may not justify preprocessing; updates would require maintaining the index lists. No measured crossover or speedup is available.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2029635919/) displayed the following at capture on **2026-11-02T13:44:19.079Z**:

- Runtime: **59 ms**; reported runtime `Beats`: **41.67%**.
- Memory: **118.58 MB**; reported memory `Beats`: **83.33%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Directly indexes arrays with values and assumes the documented 1..10000 domain, valid query bounds, and successful allocations. An out-of-domain query value can access outside the counts array; absent in-range values correctly return zero.

- Unchecked malloc/calloc results
- Fixed value-domain indexing

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
