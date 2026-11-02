# 0083 — Remove Duplicates from Sorted List

[Problem](https://leetcode.com/problems/remove-duplicates-from-sorted-list/) · [Accepted submission](https://leetcode.com/submissions/detail/2033723539/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 168 / 168 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 15, 2026 14:35**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Walk the sorted list and compare each node with its successor. Equal successors are unlinked and freed while the current node stays in place, allowing a whole duplicate run to collapse. Advance only when the next value differs.

## Complexity

- Time: O(n), where n is the number of list nodes
- Auxiliary space / ownership: O(1) auxiliary space; list links are modified and removed nodes are freed

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Build a new list of unique sorted values. Scan the original list and allocate one new node per distinct value.

- Baseline time: O(n). Space: O(u) newly allocated output nodes for u distinct values; O(1) other state.
- Submitted approach: Unlink and free duplicate nodes. Time: O(n), where n is the number of list nodes. Space: O(1) auxiliary space; list links are modified and removed nodes are freed.

**How much, by analysis:** Both inspect a linear number of links. The copy baseline allocates u output nodes; the archived source allocates no new nodes and frees n-u duplicates. This compares allocation volume, not elapsed time or universal memory safety.

**Why:** Reusing the existing unique nodes avoids building an independent output list.

**Trade-offs and conditions:** Requires ownership compatible with freeing removed nodes and invalidates aliases to them. A copied output preserves the original list and its node identities.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2033723539/) displayed the following at capture on **2026-11-02T13:52:10.839Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **11.82 MB**; reported memory `Beats`: **7.43%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

The list must be sorted and duplicate nodes must be individually compatible with free. External aliases to removed nodes become invalid; this routine is not appropriate for stack-allocated nodes or a caller retaining those aliases.

- Frees caller-supplied duplicate nodes; ownership must permit that.
- Judge-provided ListNode structure is required.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
