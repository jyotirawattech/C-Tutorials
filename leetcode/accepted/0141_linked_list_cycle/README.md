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

## Assumptions and review notes

All traversed nodes and next pointers must remain valid and stable during the call. The method does not validate dangling pointers or concurrent mutations, and the fragment requires the judge's ListNode definition and bool/NULL declarations.

- No allocation or dangerous library call observed.
- Judge-provided ListNode, bool and NULL definitions are required.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
