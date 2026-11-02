# 0328 — Odd Even Linked List

[Problem](https://leetcode.com/problems/odd-even-linked-list/) · [Accepted submission](https://leetcode.com/submissions/detail/2033789935/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 70 / 70 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 15, 2026 15:34**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Maintain separate next-pointer chains for nodes at odd and even positions while scanning the original list. Save the even head before rewiring, and append that chain after the odd tail when traversal ends. Relative order is preserved within each positional group.

## Complexity

- Time: O(n), where n is list length.
- Auxiliary space / ownership: O(1) auxiliary pointers.

## Assumptions and review notes

Groups by one-based node position, not by numeric value parity. It mutates the original next links and requires an acyclic finite list plus the judge ListNode definition. Empty and single-node inputs return unchanged.

- Input list mutation
- External judge ListNode support type

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
