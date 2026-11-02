# 0485 — Max Consecutive Ones

[Problem](https://leetcode.com/problems/max-consecutive-ones/) · [Accepted submission](https://leetcode.com/submissions/detail/2032923073/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 45 / 45 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 14, 2026 20:17**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Maintain the length of the current run and the best completed-or-current run seen so far. For binary inputs, multiplying the updated current count by the current element resets it at zero and extends it at one. Compare that count with the running maximum on each element.

## Complexity

- Time: O(n), where n=numsSize
- Auxiliary space / ownership: O(1) auxiliary space

## How this solution compares

**Conclusion:** Same or worse against this comparator.

**Named baseline:** Branch-based consecutive-ones counter. If the current value is one increment the run, otherwise reset it; update the maximum.

- Baseline time: O(n). Space: O(1).
- Submitted approach: Arithmetic reset of the consecutive-ones counter. Time: O(n), where n=numsSize. Space: O(1) auxiliary space.

**How much, by analysis:** Both perform n run updates and at most n maximum checks. The archive replaces a reset branch with arithmetic; actual machine branches, instruction cost and prediction behavior are compiler/input dependent. No 'how many times faster' claim is established.

**Why:** Multiplication resets or extends the run for binary values, but computes the same linear scan as a straightforward conditional.

**Trade-offs and conditions:** Arithmetic requires the binary-value contract. The conditional version is more explicit; source-level branchless arithmetic alone is not a measured improvement.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2032923073/) displayed the following at capture on **2026-11-02T13:43:57.845Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **13.29 MB**; reported memory `Beats`: **54.15%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

The arithmetic reset assumes every value is exactly zero or one. Values outside the binary domain do not represent a consecutive-ones count, and this source does not validate that contract.

- No allocation or dangerous library call observed.
- 'Branchless' source arithmetic does not prove branchless machine code or faster execution.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
