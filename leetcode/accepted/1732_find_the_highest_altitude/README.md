# 1732 — Find the Highest Altitude

[Problem](https://leetcode.com/problems/find-the-highest-altitude/) · [Accepted submission](https://leetcode.com/submissions/detail/2037096592/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 80 / 80 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 18, 2026 10:54**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Accumulate each altitude change from an initial altitude of zero. Keep the largest prefix sum seen so far, including the starting altitude. Every visited point is considered once without storing the complete route.

## Complexity

- Time: O(n), where n is the number of altitude changes.
- Auxiliary space / ownership: O(1) auxiliary state.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Materialize all prefix altitudes. Store the starting altitude and every cumulative altitude, then find the maximum.

- Baseline time: O(n). Space: O(n) altitude array.
- Submitted approach: Streaming altitude maximum. Time: O(n). Space: O(1).

**How much, by analysis:** The archive replaces n+1 stored altitudes with two integers and combines accumulation/maximum checks in one pass. Time growth stays linear; no elapsed speedup is claimed.

**Why:** Only the current altitude and largest altitude are needed when returning one maximum.

**Trade-offs and conditions:** Does not retain the route for later queries, and cumulative altitude must fit int. The benefit is storage relative to a materialized-route baseline.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2037096592/) displayed the following at capture on **2026-11-02T13:51:14.452Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **9.04 MB**; reported memory `Beats`: **22.93%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

The cumulative altitude uses int and assumes the problem's bounded sums. Empty input returns the starting altitude zero. Exercise an entirely descending route and a later climb whose peak exceeds the starting point.

- Integer-accumulation bound

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
