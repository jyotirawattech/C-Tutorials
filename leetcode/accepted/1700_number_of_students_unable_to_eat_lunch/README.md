# 1700 — Number of Students Unable to Eat Lunch

[Problem](https://leetcode.com/problems/number-of-students-unable-to-eat-lunch/) · [Accepted submission](https://leetcode.com/submissions/detail/2033035894/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 55 / 55 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 14, 2026 22:17**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Count how many students prefer each sandwich type instead of simulating queue rotations. Process sandwiches in stack order, consuming one matching preference when available. Once no remaining student wants the next sandwich, further rotations cannot help and the remaining counts give the answer.

## Complexity

- Time: O(n + m), for n students and m sandwiches.
- Auxiliary space / ownership: O(1) auxiliary counters.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Literal queue-rotation simulation. Rotate students who reject the next sandwich, stopping after a complete unsuccessful round.

- Baseline time: O(n*m) conservative worst-case rotations for n students and m sandwiches. Space: O(n) explicit queue.
- Submitted approach: Preference counts. Time: O(n+m). Space: O(1), two counters.

**How much, by analysis:** The archive counts n students once and inspects at most m sandwiches, avoiding repeated queue rotations and queue storage. This is an operation-growth comparison, not a measured time ratio.

**Why:** Only availability of each binary preference matters: rotations cannot help once no remaining student wants the next sandwich.

**Trade-offs and conditions:** Depends on the binary preference domain and the problem's freely rotating queue rules. Other scheduling constraints would invalidate the aggregate-count model.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2033035894/) displayed the following at capture on **2026-11-02T13:42:09.555Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **8.95 MB**; reported memory `Beats`: **24.59%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Indexes a two-element array with every preference and sandwich value, so values must be exactly 0 or 1. The intended problem supplies equal-sized arrays; invalid values would index out of bounds. Exercise an immediately blocked sandwich and a sequence all students can consume.

- Direct indexing relies on binary input domain

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
