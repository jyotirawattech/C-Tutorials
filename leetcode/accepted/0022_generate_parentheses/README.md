# 0022 — Generate Parentheses

[Problem](https://leetcode.com/problems/generate-parentheses/) · [Accepted submission](https://leetcode.com/submissions/detail/2046778526/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 8 / 8 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 26, 2026 17:20**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Build each sequence with backtracking, adding an opening parenthesis while fewer than n have been used and a closing one only while fewer closes than opens have been used. Those conditions keep every partial sequence balanced and potentially completable. Copy a finished 2n-character sequence into its own returned allocation.

## Complexity

- Time: O(n*C_n), where C_n is the nth Catalan number and each emitted sequence has length 2n.
- Auxiliary space / ownership: O(n) working buffer and recursion depth, plus O(n*C_n) returned strings and a fixed 1500-pointer result buffer.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Generate every bracket string and validate. Enumerate all length-2n strings over two bracket choices, then check balance.

- Baseline time: O(n*4^n). Space: O(n) working space plus valid output.
- Submitted approach: Prefix-valid backtracking. Time: O(n*C_n), where C_n is the nth Catalan number. Space: O(n) working/recursion plus O(n*C_n) output and a fixed 1500-pointer table.

**How much, by analysis:** At n=8 the exhaustive baseline considers 65536 complete bracket strings, while 1430 valid strings must be emitted. The archive prunes invalid prefixes; these candidate/output counts are not an elapsed-time ratio.

**Why:** The open/close constraints reject invalid prefixes before constructing their remaining suffixes.

**Trade-offs and conditions:** The archive still has unavoidable exponential output and relies on n<=8 for its fixed result capacity. Allocation failures are unchecked; small n need not yield a measurable speed advantage.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2046778526/) displayed the following at capture on **2026-11-02T13:48:02.114Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **9.97 MB**; reported memory `Beats`: **70.57%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

The result capacity is chosen for n <= 8 and has no general growth check. Allocations are unchecked; strcpy copies into an exactly sized destination only under the established sequence-length invariant. The caller must free every result string and the pointer array.

- Fixed result capacity depends on n<=8
- Unchecked allocations and strcpy
- Requires platform allocation/string declarations or wrapper

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
