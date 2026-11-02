# 1768 — Merge Strings Alternately

[Problem](https://leetcode.com/problems/merge-strings-alternately/) · [Accepted submission](https://leetcode.com/submissions/detail/2041859979/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 108 / 108 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 22, 2026 13:30**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Advance one cursor through each string and append one character from each while both still have characters. Once a string ends, copy the remaining suffix of the other string. Append a terminator after the combined prefix reaches the sum of the two lengths.

## Complexity

- Time: O(a+b), for input string lengths a and b, including their initial length scans.
- Auxiliary space / ownership: O(1) auxiliary cursors, plus O(a+b) returned string.

## How this solution compares

**Conclusion:** Improvement not established.

**Named baseline:** Preallocated indexed alternating merge. Measure lengths, allocate combined output and alternate characters using indices.

- Baseline time: O(a+b). Space: O(1) work state plus O(a+b) output.
- Submitted approach: Two read cursors and output cursor. Time: O(a+b). Space: O(1) work state plus O(a+b) output.

**How much, by analysis:** Both write exactly a+b characters and one terminator after length scans. No lower asymptotic work, output storage or measured constant-factor advantage is established.

**Why:** The archive is a conventional preallocated merge; separate tail loops handle unequal lengths cleanly.

**Trade-offs and conditions:** Requires valid terminated strings and safe length/allocation arithmetic. The checked output allocation belongs to the caller; code clarity is not a numeric speed metric.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2041859979/) displayed the following at capture on **2026-11-02T13:49:14.689Z**:

- Runtime: **3 ms**; reported runtime `Beats`: **33.19%**.
- Memory: **8.67 MB**; reported memory `Beats`: **56.62%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Requires valid terminated strings and combined lengths representable by int and the allocation size calculation. Allocation failure is checked; the caller owns the result. Exercise equal-length strings, unequal tails and an empty string where the calling contract permits it.

- String termination and integer-length preconditions

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
