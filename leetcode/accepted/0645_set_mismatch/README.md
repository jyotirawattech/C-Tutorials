# 0645 — Set Mismatch

[Problem](https://leetcode.com/problems/set-mismatch/) · [Accepted submission](https://leetcode.com/submissions/detail/2032936506/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 49 / 49 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 14, 2026 20:32**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

XOR the supplied values with the expected range 1..n to isolate duplicate XOR missing. Partition both collections using a distinguishing set bit to recover the two candidates. Scan the input once more to decide which candidate is the duplicate.

## Complexity

- Time: O(n), where n=numsSize
- Auxiliary space / ownership: O(1) auxiliary space; a two-integer returned allocation

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Frequency array for 1..n. Count every value and scan the n counters for the zero and repeated count.

- Baseline time: O(n). Space: O(n) auxiliary counters plus the two-value result.
- Submitted approach: XOR partition plus duplicate identification. Time: O(n), where n=numsSize. Space: O(1) auxiliary space; a two-integer returned allocation.

**How much, by analysis:** The baseline stores n+1 counters. The archive has constant-sized counters/masks and a two-value result, using two complete XOR/partition passes and up to one more input scan. Both have linear work growth; a speed improvement is not established.

**Why:** XOR cancels matched values and separates the two anomalies using one distinguishing bit, avoiding n frequency counters.

**Trade-offs and conditions:** Requires exactly one duplicate and one missing value in the stated range. XOR reasoning is less direct than frequency counting, and the result allocation is unchecked.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2032936506/) displayed the following at capture on **2026-11-02T13:43:54.109Z**:

- Runtime: **1 ms**; reported runtime `Beats`: **42.03%**.
- Memory: **10.10 MB**; reported memory `Beats`: **72.17%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

The contract requires exactly one duplicated value and one missing value in the range 1..n. The returned pair is heap allocated and must be freed by the caller; allocation failure is not checked.

- Unchecked result malloc.
- Unsigned negation is used for bit isolation; the assigned int mask still relies on the bounded problem domain for a straightforward portable interpretation.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
