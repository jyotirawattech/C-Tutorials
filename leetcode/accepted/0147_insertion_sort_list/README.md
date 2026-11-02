# 0147 — Insertion Sort List

[Problem](https://leetcode.com/problems/insertion-sort-list/) · [Accepted submission](https://leetcode.com/submissions/detail/2040538204/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 19 / 19 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 21, 2026 09:44**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Build a sorted prefix behind a stack-allocated dummy node. Save the next unsorted node, scan the sorted prefix for its insertion position, and splice the current node into that position. Saving the original next link allows traversal to continue after rewiring.

## Complexity

- Time: O(n^2) worst case; O(n) when each next node inserts immediately at the front
- Auxiliary space / ownership: O(1) auxiliary space; existing list nodes are relinked

## Assumptions and review notes

The function mutates list links and assumes an acyclic valid input list. Because the search stops before equal values, later equal-valued nodes are inserted before earlier ones, so this implementation is not stable.

- No new heap allocation; the dummy node's address does not escape because only dummy.next is returned.
- Judge-provided ListNode structure is required.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
