# 1944 — Number of Visible People in a Queue

[Problem](https://leetcode.com/problems/number-of-visible-people-in-a-queue/) · [Accepted submission](https://leetcode.com/submissions/detail/2049493001/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 42 / 42 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 29, 2026 08:59**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Sweep from right to left with a monotonic stack of remaining visible height barriers. A new person can see every shorter person popped from the stack, plus the first remaining taller barrier if one exists. Each height enters and leaves the stack at most once.

## Complexity

- Time: O(n), where n is the number of people.
- Auxiliary space / ownership: O(n) auxiliary stack and O(n) returned counts.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Scan rightward visibility for each person. For each starting person, walk right while tracking the blocking horizon.

- Baseline time: O(n^2) worst case. Space: O(1) working state plus O(n) output.
- Submitted approach: Right-to-left monotonic stack. Time: O(n). Space: O(n) working stack plus O(n) output.

**How much, by analysis:** A naive scan can consider n(n-1)/2 observer/right-person pairs. The archive pushes each height once and pops it at most once, plus one surviving-barrier check per person. No timing ratio is derived.

**Why:** Shorter horizons that are popped cannot matter to future left-side observers, so repeated suffix scans are avoided.

**Trade-offs and conditions:** Uses extra linear stack storage and the distinct-height visibility model. Small inputs may not amortize allocation overhead; source hardware comments are not benchmarks.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2049493001/) displayed the following at capture on **2026-11-02T13:47:14.671Z**:

- Runtime: **2 ms**; reported runtime `Beats`: **94.80%**.
- Memory: **54.90 MB**; reported memory `Beats`: **51.06%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Uses the problem's distinct-height visibility model and valid nonnegative size. Both allocation failures are checked, but a failure returns NULL while returnSize still contains the requested length; callers must check the pointer. Heap-allocation commentary is not a measured claim about every embedded target's stack limits.

- Requires platform-provided allocation declarations or a separate standard-header wrapper
- Return-size value remains nonzero on allocation failure
- Hardware commentary is not benchmarking evidence

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
