# 1967 — Number of Strings That Appear as Substrings in Word

[Problem](https://leetcode.com/problems/number-of-strings-that-appear-as-substrings-in-word/) · [Accepted submission](https://leetcode.com/submissions/detail/2049518696/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 82 / 82 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 29, 2026 09:35**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Visit every pattern and use substring search to determine whether it occurs anywhere in the word. Increment the count once per matching pattern, regardless of how often that pattern appears in the word. Duplicate pattern entries are therefore counted separately.

## Complexity

- Time: Sum of substring-search costs over all P patterns; a naive search bound is O(P*W*Lmax), where W is word length and Lmax maximum pattern length. Actual strstr implementation cost is platform-dependent.
- Auxiliary space / ownership: O(1) explicit counter state; any library search workspace is implementation-dependent

## How this solution compares

**Conclusion:** Improvement not established.

**Named baseline:** Explicit naive substring search for each pattern. For every pattern, try each possible starting position and compare characters.

- Baseline time: O(P*W*Lmax) naive upper bound. Space: O(1) explicit search state.
- Submitted approach: One libc strstr call per pattern. Time: Sum of substring-search costs over all P patterns; a naive search bound is O(P*W*Lmax), where W is word length and Lmax maximum pattern length. Actual strstr implementation cost is platform-dependent.. Space: O(1) explicit counter state; any library search workspace is implementation-dependent.

**How much, by analysis:** The archive makes P strstr calls instead of P explicit search procedures. That alone says nothing about the number of character comparisons; a libc may optimize searches, but no version-specific work count or benchmark was established. No quantitative advantage is claimed.

**Why:** Using the library expresses the same substring predicate clearly, but its implementation is a separate platform detail.

**Trade-offs and conditions:** Library reuse reduces custom matching code. It assumes valid NUL-terminated strings, and actual time/workspace are libc-dependent.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2049518696/) displayed the following at capture on **2026-11-02T13:47:11.081Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **9.05 MB**; reported memory `Beats`: **64.44%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

All inputs must be valid NUL-terminated strings. Matching is case-sensitive byte-string matching, and the source relies on a judge-provided string.h declaration rather than including it.

- Uses strstr, flagged by the selected safe-C guidance; original archived code is preserved rather than silently replaced.
- Missing string.h/NULL declaration in the captured fragment.
- Source 'L1 cache almost instantly' claim is not supported by an execution or benchmark.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
