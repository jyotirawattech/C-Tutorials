# 0686 — Repeated String Match

[Problem](https://leetcode.com/problems/repeated-string-match/) · [Accepted submission](https://leetcode.com/submissions/detail/2033715692/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 62 / 62 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 15, 2026 14:28**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Construct enough repeats of a to reach b's length and search that buffer for b. If there is no match, append one additional copy and search again; the extra copy covers a match beginning near a repetition boundary. Return the first sufficient repetition count or -1.

## Complexity

- Time: O(a+b) buffer construction, plus two substring searches; a conservative portable bound is O((a+b)*b) if substring search is naive, where a and b denote input lengths.
- Auxiliary space / ownership: O(a+b) allocated repeated buffer.

## How this solution compares

**Conclusion:** Same or worse against this comparator.

**Named baseline:** Pattern matching on a virtual repeated string. Run KMP over repeated source characters without materializing the whole repeat buffer.

- Baseline time: O(a+b). Space: O(b) prefix table.
- Submitted approach: Materialize bounded repeats and call strstr. Time: O(a+b) copying plus two searches; conservative O((a+b)*b) with naive substring search. Space: O(a+b) repeated buffer.

**How much, by analysis:** The archive makes at most two substring-search calls after constructing ceil(b/a) copies plus at most one extra. Those two calls do not imply linear search work or a speed advantage over KMP.

**Why:** The repeat-count bound is useful, but the source delegates matching to strstr and does not establish a better bound than a linear pattern matcher.

**Trade-offs and conditions:** Simpler implementation can help readability, while extra buffer storage and library-dependent search cost remain. Empty a divides by zero; integer sizes are constrained. SIMD behavior is not measured.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2033715692/) displayed the following at capture on **2026-11-02T13:52:14.429Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **9.02 MB**; reported memory `Beats`: **27.78%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Requires a nonempty source string and valid terminated inputs; empty a would divide by zero. Lengths/allocation arithmetic use int and rely on problem bounds. The checked allocation is freed on every completed path; memcpy sizes depend on those computed bounds, and the SIMD comment is not measured evidence.

- Nonempty divisor/string precondition
- memcpy buffer bounds depend on length arithmetic
- Unverified SIMD commentary

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
