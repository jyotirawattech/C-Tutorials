# 0482 — License Key Formatting

[Problem](https://leetcode.com/problems/license-key-formatting/) · [Accepted submission](https://leetcode.com/submissions/detail/2033701198/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 40 / 40 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 15, 2026 14:14**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Count non-dash characters to determine the exact formatted length, then fill the output from right to left. Insert a dash after every k retained characters and convert lowercase ASCII letters to uppercase. Backward filling naturally permits the first group to be shorter than the later groups.

## Complexity

- Time: O(n), where n is the input string length.
- Auxiliary space / ownership: O(1) auxiliary state, plus O(n) returned string.

## How this solution compares

**Conclusion:** Improvement not established.

**Named baseline:** Count and forward-fill formatted output. Count retained characters, compute the first group length, then fill an exact-sized output buffer.

- Baseline time: O(n). Space: O(1) auxiliary state plus O(n) output.
- Submitted approach: Count and backward-fill output. Time: O(n). Space: O(1) auxiliary state plus O(n) output.

**How much, by analysis:** Both scan n source characters for counting and up to n again for formatting, with one sized output allocation. No asymptotic or measured runtime improvement is established.

**Why:** Backward grouping makes the short leading group fall out naturally, but it does not reduce the two-pass linear work versus a forward fill.

**Trade-offs and conditions:** Requires k>0, ASCII case mapping and bounded lengths. Allocations are unchecked; backward filling is a presentation choice rather than proof of better performance.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2033701198/) displayed the following at capture on **2026-11-02T13:52:41.227Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **9.49 MB**; reported memory `Beats`: **62.50%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Requires a terminated input, k>0, and lengths fitting int. Character conversion assumes ASCII's lowercase-to-uppercase offset; it does not implement locale-aware or Unicode casing. Both result allocations are unchecked, and the caller owns the result.

- Unchecked malloc results
- Positive divisor and ASCII assumptions

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
