# 1441 — Build an Array With Stack Operations

[Problem](https://leetcode.com/problems/build-an-array-with-stack-operations/) · [Accepted submission](https://leetcode.com/submissions/detail/2032945463/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 49 / 49 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 14, 2026 20:43**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Walk the stream of integers from one until all target values are reached. Emit Push for each stream value; emit an additional Pop when that value is not the next target element. The retained values therefore match the processed prefix of the strictly increasing target.

## Complexity

- Time: O(m), where m is the largest target value
- Auxiliary space / ownership: O(1) auxiliary state; O(m) returned operation-pointer allocation

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Allocate and copy each output operation string. Generate the same Push/Pop sequence but allocate a separate string for each emitted operation.

- Baseline time: O(m) for largest target m and O(m) short output strings. Space: O(m) pointer output plus separately allocated operation-string payloads.
- Submitted approach: Operation pointers to shared string literals. Time: O(m), where m is the largest target value. Space: O(1) auxiliary state; O(m) returned operation-pointer allocation.

**How much, by analysis:** For p emitted operations, the comparator makes p string allocations in addition to its pointer-array allocation. The archive makes one pointer-array allocation and reuses two literals, eliminating those p per-string allocations/copies. No milliseconds or allocator-byte ratio is established.

**Why:** The output sequence is identical, but constant operation labels can be shared rather than copied per output item.

**Trade-offs and conditions:** Consumers must free only the pointer array, never the literals or write through them. The target must be nonempty/increasing and the output allocation is unchecked.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2032945463/) displayed the following at capture on **2026-11-02T13:43:00.716Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **9.70 MB**; reported memory `Beats`: **44.62%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

The target must be nonempty, strictly increasing and covered by the stream bound n. The returned array contains pointers to read-only string literals: free the pointer array only, not each Push/Pop string.

- Unchecked result malloc.
- Returning string literals differs from independently allocated result strings; consumers must respect that ownership boundary.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
