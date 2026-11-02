# 3532 — Path Existence Queries in a Graph I

[Problem](https://leetcode.com/problems/path-existence-queries-in-a-graph-i/) · [Accepted submission](https://leetcode.com/submissions/detail/2061378248/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 550 / 550 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jul 09, 2026 12:19**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Scan the sorted values and begin a new component whenever the gap between adjacent values exceeds maxDiff. Within a component, the adjacent-value chain supplies a path; across a larger gap, no permitted edge can connect the two sides. Each query therefore needs only a comparison of the two stored component labels.

## Complexity

- Time: O(n + q), for n nodes and q queries.
- Auxiliary space / ownership: O(n) component labels and O(q) returned answers.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Build threshold graph and traverse per query. Test all node pairs for edges, then run BFS/DFS for each reachability query.

- Baseline time: O(n^2+q*(n+e)), for e edges and q queries. Space: O(n+e) graph/traversal storage plus answers.
- Submitted approach: Sorted-gap component labels. Time: O(n+q). Space: O(n) labels plus O(q) answers.

**How much, by analysis:** The archive examines n-1 adjacent gaps and compares two labels per query. It avoids testing n(n-1)/2 possible edges and repeated traversals in the stated baseline. These work counts do not establish an elapsed-time multiplier.

**Why:** Sorted adjacent gaps completely determine connected components: every small-gap run has a connecting chain, and a large gap cannot be crossed by any permitted edge.

**Trade-offs and conditions:** Requires sorted values and this specific difference-threshold graph. It is not a general replacement for graph traversal; shape/index checks and arithmetic bounds are trusted, and the source's cache guarantee is unmeasured.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2061378248/) displayed the following at capture on **2026-11-02T13:46:59.860Z**:

- Runtime: **2 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **61.35 MB**; reported memory `Beats`: **84.62%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Requires n == numsSize > 0, sorted nums, two valid node indices per query, and safe integer differences under the problem bounds. Source comments claiming guaranteed L1-cache behavior are unmeasured and should not be treated as performance evidence. Allocation failures return NULL rather than answers.

- Requires platform-provided bool/allocation declarations or a separate wrapper
- Input shape, index and integer-difference preconditions
- Unverified cache-guarantee commentary

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
