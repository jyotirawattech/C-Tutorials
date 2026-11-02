# 1590 — Make Sum Divisible by P

[Problem](https://leetcode.com/problems/make-sum-divisible-by-p/) · [Accepted submission](https://leetcode.com/submissions/detail/2040516582/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 145 / 145 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 21, 2026 09:22**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Compute the total remainder modulo p, then scan prefix remainders. For each prefix, look up the complementary earlier remainder whose removal would cancel the total remainder. Store the most recent index for every remainder so matching candidates are as short as possible, and reject removal of the full array.

## Complexity

- Time: Expected O(n+H) with distributed hash chains, O(n^2+H) worst case from collisions; H=100003 bucket slots.
- Auxiliary space / ownership: O(H+min(n+1,p)) for hash buckets and distinct prefix-remainder nodes.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Enumerate removable subarrays. Extend each left boundary while maintaining the removed sum modulo p.

- Baseline time: O(n^2). Space: O(1).
- Submitted approach: Most-recent prefix remainder hash. Time: Expected O(n+H), worst O(n^2+H); H=100003. Space: O(H+min(n+1,p)).

**How much, by analysis:** The baseline may consider n(n+1)/2 intervals. The archive performs up to two hash-chain operations per endpoint plus table initialization/cleanup; short-chain behavior is assumed for expected linear work, not a guaranteed speed ratio.

**Why:** The needed earlier prefix remainder identifies a valid removal without enumerating every possible start. The latest matching index minimizes length for the current end.

**Trade-offs and conditions:** Extra hash storage/init cost can dominate small n; collisions restore quadratic worst-case work. Positive p, nonnegative values, bounded sums and successful allocations are assumed.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2040516582/) displayed the following at capture on **2026-11-02T13:51:10.664Z**:

- Runtime: **105 ms**; reported runtime `Beats`: **13.67%**.
- Memory: **70.41 MB**; reported memory `Beats`: **18.63%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Assumes p>0, nonnegative problem values, and a total fitting long long. Allocations are unchecked; negative values could create negative hash indices under C remainder rules. Exercise an already-divisible total, a single-element valid removal and a case requiring forbidden whole-array removal.

- Unchecked malloc/calloc results
- Positive-modulus/nonnegative-input assumptions
- Worst-case hash collisions

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
