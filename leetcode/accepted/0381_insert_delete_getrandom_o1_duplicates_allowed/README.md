# 0381 — Insert Delete GetRandom O(1) - Duplicates allowed

[Problem](https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed/) · [Accepted submission](https://leetcode.com/submissions/detail/2029527256/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 32 / 32 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 11, 2026 14:26**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Store every occurrence in a dense array and keep separate hash-chain nodes mapping each occurrence to its array index. Removal swaps the array's last value into the removed slot and searches its bucket to repair the moved index. Random lookup chooses an array slot, so duplicated values occupy proportionally more slots.

## Complexity

- Time: getRandom O(1); insert/remove O(n) worst case because they scan hash chains, including occurrence-index repair. Constant expected time requires favorable bucket/load behavior not guaranteed by this fixed table.
- Auxiliary space / ownership: O(C+H+n) for fixed C=200005 array capacity, H=100003 buckets and n occurrence nodes

## How this solution compares

**Conclusion:** Same or worse against this comparator.

**Named baseline:** Dense occurrence array with per-value index sets. Keep an indexed set of positions for each value and repair the moved last occurrence with expected-constant hash-set operations.

- Baseline time: Expected O(1) insert/remove/getRandom under hash assumptions; worst case depends on maps. Space: O(n) occurrence/index storage plus hash metadata.
- Submitted approach: Dense occurrence array with scanned hash chains. Time: getRandom O(1); insert/remove O(n) worst case because they scan hash chains, including occurrence-index repair. Constant expected time requires favorable bucket/load behavior not guaranteed by this fixed table.. Space: O(C+H+n) for fixed C=200005 array capacity, H=100003 buckets and n occurrence nodes.

**How much, by analysis:** An archive insert/remove can traverse up to O(n) chain nodes. The named comparator uses a constant expected number of hash operations. The archive also preallocates C=200005 values and H=100003 bucket heads; no exact byte or latency gain is demonstrated.

**Why:** The archive uses the dense-array idea, but linked-chain searches and moved-index repair do not establish an advantage over proper per-value index sets.

**Trade-offs and conditions:** Fixed capacity is unchecked, getRandom requires nonempty input, and rand()%size can be biased. Both designs need a separately justified random-index method if exact uniformity matters.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2029527256/) displayed the following at capture on **2026-11-02T13:45:31.021Z**:

- Runtime: **60 ms**; reported runtime `Beats`: **68.57%**.
- Memory: **99.12 MB**; reported memory `Beats`: **50.00%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

The fixed array capacity is not checked before insertion, getRandom assumes a nonempty collection, and rand()%size can introduce modulo bias. This is judged practice code, not cryptographic randomness or an unrestricted expected-O(1) container.

- Unchecked object/array/bucket/node allocations.
- Unchecked fixed capacity and possible modulo-by-zero if getRandom is called empty.
- rand is noncryptographic; modulo selection is not an exact-uniformity guarantee.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
