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

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Recursive build with inorder linear searches. For each subtree root, scan its inorder range to locate the split.

- Baseline time: O(n^2) worst case. Space: O(h) recursion plus O(n) returned nodes.
- Submitted approach: Direct value-to-inorder lookup. Time: O(n+V), V=6001. Space: O(V+h) auxiliary storage plus O(n) returned nodes.

**How much, by analysis:** The baseline can inspect n+(n-1)+...+1 inorder positions on a skewed case. The archive initializes V slots and maps/constructs each of n nodes once. No timing ratio follows from those counts.

**Why:** A precomputed bounded-domain index replaces repeated inorder scans with constant-time root-position lookup.

**Trade-offs and conditions:** Extra fixed lookup storage may dominate tiny inputs. Unique values in -3000..3000 and matching traversals are required; recursion remains O(n) in a skewed tree and allocations are unchecked.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2041565369/) displayed the following at capture on **2026-11-02T13:49:21.390Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **16.24 MB**; reported memory `Beats`: **5.86%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Assumes matching traversals with unique values in -3000..3000 and requires the platform TreeNode definition. Invalid traversal sizes/values can cause bad indexing, and node allocation failures are unchecked. A skewed tree can require O(n) recursive depth; the returned tree requires caller cleanup.

- Fixed shifted value-domain map
- Unchecked malloc result
- Potential deep recursion
- External judge-provided TreeNode support type

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
