# 3756 — Concatenate Non-Zero Digits and Multiply by Sum II

[Problem](https://leetcode.com/problems/concatenate-non-zero-digits-and-multiply-by-sum-ii/) · [Accepted submission](https://leetcode.com/submissions/detail/2060383645/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 523 / 523 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jul 08, 2026 16:04**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Precompute prefix digit sums, counts of retained nonzero digits, retained-digit values modulo 1000000007, and powers of ten. For each range, subtract the earlier retained prefix after shifting it by the range's nonzero-digit count, then multiply by the range's digit sum. Modular normalization handles a negative subtraction before multiplication.

## Complexity

- Time: O(m + q), for string length m and q queries.
- Auxiliary space / ownership: O(m) auxiliary prefix arrays and O(q) returned answers.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Rebuild filtered digits for every query. Scan each substring, append its nonzero digits modulo MOD and sum its digits.

- Baseline time: O(sum of query widths), at most O(q*m). Space: O(1) working arithmetic state plus output.
- Submitted approach: Prefix sums, retained-digit prefixes and powers. Time: O(m+q). Space: O(m) four auxiliary arrays plus O(q) output.

**How much, by analysis:** The baseline revisits every queried character. The archive performs one m-character preprocessing pass and a bounded number of arithmetic/array operations per query; benefit depends on total query width exceeding setup work. No measured speedup is asserted.

**Why:** Prefix differences recover digit sums and retained-digit counts, while modular prefix removal recovers each filtered number without rescanning the substring.

**Trade-offs and conditions:** Preprocessing can be unnecessary for one short query and uses several full-length arrays. Partial allocation failure leaks successful allocations; index/arithmetic assumptions remain. Source kernel/stack comments are not validated performance evidence.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2060383645/) displayed the following at capture on **2026-11-02T13:47:03.229Z**:

- Runtime: **30 ms**; reported runtime `Beats`: **18.18%**.
- Memory: **107.09 MB**; reported memory `Beats`: **9.09%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Requires a terminated decimal string, valid inclusive query bounds, and problem-bounded arithmetic. If any allocation fails, the early NULL return leaks allocations that already succeeded; normal completion frees the four auxiliary arrays. The source's kernel-panic/stack commentary is not verified and does not describe ordinary user-space stack failure accurately.

- Known partial-allocation failure leak
- Requires platform-provided string/allocation declarations or wrapper
- Unverified hardware/kernel-panic commentary

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
