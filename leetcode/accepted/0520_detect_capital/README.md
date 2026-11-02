# 0520 — Detect Capital

[Problem](https://leetcode.com/problems/detect-capital/) · [Accepted submission](https://leetcode.com/submissions/detail/2033696432/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 553 / 553 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 15, 2026 14:09**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Use the first two characters to choose whether the rest must all be uppercase or all be lowercase. Reject a lowercase first character followed by an uppercase second character immediately. Then scan the remaining characters and require their uppercase status to match the chosen pattern.

## Complexity

- Time: O(n), where n is word length.
- Auxiliary space / ownership: O(1) auxiliary state.

## How this solution compares

**Conclusion:** Improvement not established.

**Named baseline:** Count uppercase characters. Count uppercase letters and accept none, all, or exactly the first character.

- Baseline time: O(n). Space: O(1).
- Submitted approach: Infer case pattern then short-circuit. Time: O(n) worst case. Space: O(1).

**How much, by analysis:** Worst-case inspection remains n characters for both approaches. Earlier rejection can save suffix checks on some invalid words, but its frequency and elapsed benefit have not been measured.

**Why:** The first two letters determine the permitted case of later letters, allowing rejection at the first conflict.

**Trade-offs and conditions:** Assumes English letters and a valid terminated string; non-uppercase punctuation would be treated as lowercase. No universal superiority over an equally linear baseline is established.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2033696432/) displayed the following at capture on **2026-11-02T13:52:45.068Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **8.52 MB**; reported memory `Beats`: **44.40%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Assumes a valid terminated string of English letters. Any non-uppercase character is treated as lowercase, so arbitrary punctuation/digits are outside the validation contract; Unicode casing is unsupported. Empty and one-character strings return true.

- Terminated English-letter input precondition

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
