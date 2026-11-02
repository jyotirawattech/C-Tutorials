# 3739 — Count Subarrays With Majority Element II

[Problem](https://leetcode.com/problems/count-subarrays-with-majority-element-ii/) · [Accepted submission](https://leetcode.com/submissions/detail/2046769368/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 516 / 516 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 26, 2026 17:09**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Map each target occurrence to +1 and every other value to -1, so a subarray has a strict target majority exactly when its sum is positive. Count earlier prefix sums smaller than the current prefix. Because each step changes the prefix by exactly one, update that smaller-prefix count using only the frequency at the crossed boundary, then accumulate and record the current prefix.

## Complexity

- Time: O(n), including initialization of O(n) frequency slots
- Auxiliary space / ownership: O(n) auxiliary frequency array; counters use long long for the total

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Extend every subarray and count its target frequency. For each start position, incrementally count target/non-target values for every end position and test majority.

- Baseline time: O(n^2). Space: O(1) auxiliary.
- Submitted approach: One-step prefix-frequency majority counting. Time: O(n), including initialization of O(n) frequency slots. Space: O(n) auxiliary frequency array; counters use long long for the total.

**How much, by analysis:** The baseline examines n(n+1)/2 subarray extensions. The archive performs n prefix transitions plus initialization of 2n+3 frequency slots. This is a candidate/work-structure comparison, not a stopwatch speedup or a universal constant-factor guarantee.

**Why:** Mapping target to +1 turns majority into a positive subarray sum; prefix sums change by one, so a frequency at one boundary updates the count of valid earlier prefixes.

**Trade-offs and conditions:** Uses O(n) frequency storage and wider total counters. Returning zero on allocation failure is ambiguous, and size arithmetic depends on judged bounds.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2046769368/) displayed the following at capture on **2026-11-02T13:48:28.952Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **21.36 MB**; reported memory `Beats`: **47.06%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Allocation failure returns zero, which is indistinguishable from a valid zero count. Array-size arithmetic and int frequency counters rely on the judged input bounds; the captured fragment needs standard allocation declarations from its judge/wrapper.

- Missing stdlib.h declarations in the captured fragment.
- mapSize=2*numsSize+3 can overflow outside bounded inputs.
- Source hardware/thread-safety comments do not establish whole-function concurrency safety or measured speed.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
