# 0138 — Copy List with Random Pointer

[Problem](https://leetcode.com/problems/copy-list-with-random-pointer/) · [Accepted submission](https://leetcode.com/submissions/detail/2037081804/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 19 / 19 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 18, 2026 10:42**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Temporarily weave one clone immediately after every original node. An original random pointer's target clone is then available as target->next, allowing random links to be assigned without a map. Finally unweave the chains, restoring the original next pointers and returning the independent clone list.

## Complexity

- Time: O(n), across three linear passes over n nodes.
- Auxiliary space / ownership: O(1) auxiliary pointers, plus O(n) allocated clone nodes.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Original-to-clone hash map. Allocate clones and use a map to translate original next/random pointers.

- Baseline time: Expected O(n). Space: O(n) auxiliary map plus O(n) output nodes.
- Submitted approach: Weave, connect random pointers, unweave. Time: O(n), three list passes. Space: O(1) auxiliary pointers plus O(n) output nodes.

**How much, by analysis:** The archive replaces n map entries with a constant number of working pointers while still allocating n clones. Both have linear expected traversal work; the archive uses three explicit passes.

**Why:** The clone next to each original temporarily acts as the translation map, so random targets resolve without a separate table.

**Trade-offs and conditions:** Temporarily mutates the original list, excludes concurrent readers, and has no allocation-failure rollback. The map baseline can leave the original structure untouched.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2037081804/) displayed the following at capture on **2026-11-02T13:51:21.457Z**:

- Runtime: **14 ms**; reported runtime `Beats`: **8.40%**.
- Memory: **14.90 MB**; reported memory `Beats`: **78.58%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Requires a finite next chain and random pointers that are null or refer to original nodes in that chain. It temporarily mutates the original list and is unsuitable for concurrent readers. Allocations are unchecked, so failure has no cleanup/unweave recovery; the caller owns the cloned list.

- Unchecked malloc result
- Temporary input mutation
- Requires judge-provided Node with val/next/random fields and allocation declarations

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
