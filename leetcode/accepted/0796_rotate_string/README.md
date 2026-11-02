# 0796 — Rotate String

[Problem](https://leetcode.com/problems/rotate-string/) · [Accepted submission](https://leetcode.com/submissions/detail/2033710099/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 62 / 62 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 15, 2026 14:23**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Reject unequal lengths, then concatenate the source string with itself. A string of equal length is a rotation exactly when it appears as a substring of that doubled buffer. Free the temporary buffer after the substring test.

## Complexity

- Time: O(n) copying plus substring search; conservative O(n^2) with a naive search, since the C standard does not prescribe strstr's implementation.
- Auxiliary space / ownership: O(n) allocated doubled buffer.

## How this solution compares

**Conclusion:** Improvement not established.

**Named baseline:** Try each rotation offset. Compare goal against every circular offset without constructing rotated copies.

- Baseline time: O(n^2) worst case. Space: O(1).
- Submitted approach: Doubled string with strstr. Time: O(n) copy plus libc-dependent substring search; O(n^2) under a naive substring-search model, not a C-standard complexity guarantee. Space: O(n).

**How much, by analysis:** The archive allocates 2n+1 characters and makes one substring call. A call count does not quantify that search's internal comparisons; no measured speedup or general space advantage is established.

**Why:** Doubling expresses rotation as a substring test, but strstr's algorithm is not fixed by C, so the source alone does not prove a better worst-case bound.

**Trade-offs and conditions:** Potentially concise code trades for extra storage. Checked allocation failure is returned as false, and strcpy correctness relies on the computed capacity and valid terminated inputs.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2033710099/) displayed the following at capture on **2026-11-02T13:52:18.093Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **8.57 MB**; reported memory `Beats`: **48.86%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Requires valid terminated strings and lengths for which 2*n+1 fits the allocation arithmetic. strcpy is capacity-safe here only because the buffer size is derived from the two lengths; a general adaptation should retain explicit length/bounds checks. Allocation failure returns false, conflating an error with no rotation.

- Unbounded strcpy depends on correctly computed capacity
- String termination and integer-size assumptions

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
