# 0448 — Find All Numbers Disappeared in an Array

[Problem](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/) · [Accepted submission](https://leetcode.com/submissions/detail/2032943655/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 35 / 35 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 14, 2026 20:41**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Use each value's absolute magnitude as an index into the input and mark that position negative. After marking, the remaining positive positions identify values that were never encountered. Duplicate values preserve the same negative mark instead of reversing it.

## Complexity

- Time: O(n), where n is the input length.
- Auxiliary space / ownership: O(1) auxiliary work space, plus an allocated result buffer of O(n).

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Separate presence bitmap. Mark every observed value in a new n-element bitmap, then emit unmarked positions.

- Baseline time: O(n). Space: O(n) auxiliary bitmap plus output.
- Submitted approach: Sign marks stored in the input. Time: O(n). Space: O(1) marking workspace plus an O(n) allocated output buffer.

**How much, by analysis:** The archive avoids n presence flags but still allocates n result integers. Both perform two linear passes, so total memory remains O(n) when returned storage is counted; no time advantage is measured.

**Why:** The sign of each input slot serves as its visited flag, removing the separate presence array.

**Trade-offs and conditions:** Input signs are modified, values must lie in 1..n, and allocation/abs bounds are trusted. A preserving baseline may be preferable when callers need the original data.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2032943655/) displayed the following at capture on **2026-11-02T13:43:04.065Z**:

- Runtime: **7 ms**; reported runtime `Beats`: **14.16%**.
- Memory: **36.04 MB**; reported memory `Beats`: **47.33%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Mutates the input signs and requires every original value to be in 1..n. Values outside that range can index out of bounds, and abs(INT_MIN) is invalid; the problem constraints exclude those cases. The caller owns the returned allocation.

- Unchecked malloc result
- In-place mutation
- Indexing and abs rely on constrained positive input

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
