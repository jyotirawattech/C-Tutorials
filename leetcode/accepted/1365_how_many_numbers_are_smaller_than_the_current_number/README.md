# 1365 — How Many Numbers Are Smaller Than the Current Number

[Problem](https://leetcode.com/problems/how-many-numbers-are-smaller-than-the-current-number/) · [Accepted submission](https://leetcode.com/submissions/detail/2032937879/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 103 / 103 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 14, 2026 20:34**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Count occurrences in the fixed 0..100 value domain. Replace each frequency with the number of values strictly below it by scanning the buckets in order. A final lookup per original value produces the count while preserving input order.

## Complexity

- Time: O(n+U), where n=numsSize and U=101 buckets; O(n) for this fixed domain
- Auxiliary space / ownership: O(U) auxiliary bucket storage and O(n) returned result; O(1) auxiliary for fixed U=101

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Compare every value with every other value. For each element, count how many of the other n-1 values are smaller.

- Baseline time: O(n^2). Space: O(1) auxiliary, excluding the n-result array.
- Submitted approach: Fixed-domain frequencies and prefix counts. Time: O(n+U), where n=numsSize and U=101 buckets; O(n) for this fixed domain. Space: O(U) auxiliary bucket storage and O(n) returned result; O(1) auxiliary for fixed U=101.

**How much, by analysis:** The baseline makes n(n-1) ordered value comparisons when self-pairs are skipped. The archive performs n frequency increments, a U=101 bucket sweep and n answer lookups. This is a bounded-domain work model; different operation costs prevent a fixed runtime-factor claim.

**Why:** The small 0..100 domain lets one frequency summary answer every strict-smaller query.

**Trade-offs and conditions:** Adds 101 counters and depends on all input values fitting 0..100. Out-of-range input indexes outside the bucket array, and result allocation is unchecked.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2032937879/) displayed the following at capture on **2026-11-02T13:43:07.383Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **12.14 MB**; reported memory `Beats`: **10.44%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

An input outside 0..100 indexes beyond the frequency array. The source assumes the bounded domain and a successful result allocation rather than validating either.

- Unchecked result malloc.
- Array indexing directly uses unvalidated input values under the problem contract.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
