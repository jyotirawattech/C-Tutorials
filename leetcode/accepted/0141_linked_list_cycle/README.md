# 0141 — Linked List Cycle

[Problem](https://leetcode.com/problems/linked-list-cycle/) · [Accepted submission](https://leetcode.com/submissions/detail/2043139098/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 29 / 29 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 23, 2026 14:11**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Advance one pointer by one link and another by two links. Reaching a null end establishes no cycle; if the pointers meet, they occupy the same node inside a cycle. The fast-pointer null checks protect the two-link step for a valid list.

## Complexity

- Time: O(mu+lambda) for a cyclic list with prefix length mu and cycle length lambda; O(n) for an acyclic list
- Auxiliary space / ownership: O(1) auxiliary space

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Remember every visited node address. Insert node addresses in a hash set and report a cycle when one repeats.

- Baseline time: Expected O(d) for d distinct reachable nodes. Space: O(d) stored addresses.
- Submitted approach: Floyd slow/fast pointers. Time: O(mu+lambda) for a cyclic list with prefix length mu and cycle length lambda; O(n) for an acyclic list. Space: O(1) auxiliary space.

**How much, by analysis:** The set can store d addresses plus hash metadata. Floyd uses two cursor variables and O(mu+lambda) iterations for a cycle with prefix mu and length lambda. Both have linear growth; no faster-runtime factor is established, and Floyd dereferences more links per iteration.

**Why:** Relative pointer motion detects repetition without retaining the visited set.

**Trade-offs and conditions:** The set approach can directly retain the first repeated node. Floyd requires valid stable next pointers and an additional phase if the cycle entry is needed.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2043139098/) displayed the following at capture on **2026-11-02T13:49:07.305Z**:

- Runtime: **9 ms**; reported runtime `Beats`: **80.16%**.
- Memory: **12.04 MB**; reported memory `Beats`: **6.26%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

All traversed nodes and next pointers must remain valid and stable during the call. The method does not validate dangling pointers or concurrent mutations, and the fragment requires the judge's ListNode definition and bool/NULL declarations.

- No allocation or dangerous library call observed.
- Judge-provided ListNode, bool and NULL definitions are required.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
