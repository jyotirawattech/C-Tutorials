# 0206 — Reverse Linked List

[Problem](https://leetcode.com/problems/reverse-linked-list/) · [Accepted submission](https://leetcode.com/submissions/detail/2033793518/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 28 / 28 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 15, 2026 15:37**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

The submitted primary function saves the next node, redirects the current next pointer toward the reversed prefix, then advances both cursors. That maintains a reversed processed prefix and an untouched remainder until the new head is known. A separately included recursive variant reverses the remainder before redirecting and clearing the original forward edge.

## Complexity

- Time: O(n) for either included variant, where n is list length.
- Auxiliary space / ownership: O(1) auxiliary pointers for reverseList; O(n) recursive call stack for reverseListRecursive.

## Assumptions and review notes

Both variants mutate the original list and assume a finite acyclic next chain. The recursive version can exhaust the stack on a sufficiently long list; the comments' production labels are not an independent deployment assessment. Requires the judge-provided ListNode definition.

- Input list mutation
- Recursive alternative has depth risk
- External judge ListNode support type

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
