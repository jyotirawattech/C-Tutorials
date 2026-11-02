# 0106 — Construct Binary Tree from Inorder and Postorder Traversal

[Problem](https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/) · [Accepted submission](https://leetcode.com/submissions/detail/2041565369/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 202 / 202 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 22, 2026 09:21**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Map each inorder value to its position, then consume postorder from its end so the next value is the current subtree root. The mapped inorder position partitions the subtree into left and right ranges. Build the right subtree first because reverse postorder visits root, right, then left.

## Complexity

- Time: O(n+V), for n nodes and initialization of the fixed lookup domain V=6001.
- Auxiliary space / ownership: O(V+h) auxiliary lookup/recursion for tree height h, plus O(n) returned tree nodes.

## Assumptions and review notes

Assumes matching traversals with unique values in -3000..3000 and requires the platform TreeNode definition. Invalid traversal sizes/values can cause bad indexing, and node allocation failures are unchecked. A skewed tree can require O(n) recursive depth; the returned tree requires caller cleanup.

- Fixed shifted value-domain map
- Unchecked malloc result
- Potential deep recursion
- External judge-provided TreeNode support type

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
