# 2073 — Time Needed to Buy Tickets

[Problem](https://leetcode.com/problems/time-needed-to-buy-tickets/) · [Accepted submission](https://leetcode.com/submissions/detail/2033036947/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 65 / 65 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 14, 2026 22:18**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Count how many turns each person can take before the target person buys their final ticket. People at or before the target can receive at most target tickets, while later people can receive at most target-1. Summing these capped contributions avoids simulating repeated queue rotations.

## Complexity

- Time: O(n), where n=ticketsSize
- Auxiliary space / ownership: O(1) auxiliary space

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Simulate one queue turn per purchased ticket. Rotate the queue and decrement one ticket at a time until the target person finishes.

- Baseline time: O(T) ticket events plus queue setup, where T is tickets bought before target completion. Space: O(n) explicit queue, or O(1) indices with input mutation.
- Submitted approach: Sum each person's capped ticket contribution. Time: O(n), where n=ticketsSize. Space: O(1) auxiliary space.

**How much, by analysis:** The simulation performs T=sum(i<=k,min(tickets[i],tickets[k]))+sum(i>k,min(tickets[i],tickets[k]-1)) ticket events. The archive evaluates n capped contributions. For n=100, all counts=100 and k=99, these are 10000 events versus 100 contributions; that 100:1 event-count example is not a measured time ratio.

**Why:** The target's final turn determines exactly how many visits each position can receive; a formula replaces queue events.

**Trade-offs and conditions:** Does not produce the queue's intermediate history and assumes a valid k/positive bounded counts. It preserves the input.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2033036947/) displayed the following at capture on **2026-11-02T13:42:06.066Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **8.82 MB**; reported memory `Beats`: **32.93%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

The target index must be valid and its ticket count positive. The source assumes bounded positive ticket counts so the accumulated total fits int; it does not validate arbitrary inputs.

- No allocation or dangerous library call observed.
- Source comment claims 'blistering fast ALU bounds checking'; static inspection establishes capped counting, not a speed measurement.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
