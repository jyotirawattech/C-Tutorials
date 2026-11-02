# 0459 — Repeated Substring Pattern

[Problem](https://leetcode.com/problems/repeated-substring-pattern/) · [Accepted submission](https://leetcode.com/submissions/detail/2033708350/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 130 / 130 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 15, 2026 14:21**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Build the KMP longest-proper-prefix/suffix table for every prefix of the string. The final table value identifies a possible repeating block of length n-lps[n-1]. A nonzero border and exact divisibility by that block length establish repetition.

## Complexity

- Time: O(n), where n is string length; fallback transitions are amortized linear
- Auxiliary space / ownership: O(n) auxiliary LPS array

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Try each possible repeating block length. For every candidate period up to n/2, check the string against that repeating prefix and require divisibility.

- Baseline time: O(n^2) upper bound for naive repeated full-string checks. Space: O(1) auxiliary.
- Submitted approach: KMP longest-prefix/suffix periodicity test. Time: O(n), where n is string length; fallback transitions are amortized linear. Space: O(n) auxiliary LPS array.

**How much, by analysis:** A naive candidate strategy can make up to floor(n/2) string-check attempts, each of up to n character comparisons. KMP's construction has O(n) amortized character-comparison growth. These are upper bounds; early exits and libc/compiler behavior prevent a fixed runtime factor.

**Why:** The LPS table reuses prefix-matching information instead of restarting a full check for every candidate block length.

**Trade-offs and conditions:** Uses O(n) LPS storage instead of constant auxiliary state. Allocation failure returns false, so a resource failure is not distinguishable from a nonrepeating string.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2033708350/) displayed the following at capture on **2026-11-02T13:52:21.995Z**:

- Runtime: **2 ms**; reported runtime `Beats`: **82.55%**.
- Memory: **12.54 MB**; reported memory `Beats`: **5.13%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

The string must be valid and NUL terminated with length fitting int. Allocation failure returns false, which is indistinguishable from a genuinely nonrepeating string.

- Uses strlen, flagged by selected safe-C guidance; preserved as historical source.
- Allocation failure is checked but conflated with a valid false result.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
