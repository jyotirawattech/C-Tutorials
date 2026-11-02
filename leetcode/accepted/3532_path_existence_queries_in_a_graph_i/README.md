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

## Assumptions and review notes

Requires n == numsSize > 0, sorted nums, two valid node indices per query, and safe integer differences under the problem bounds. Source comments claiming guaranteed L1-cache behavior are unmeasured and should not be treated as performance evidence. Allocation failures return NULL rather than answers.

- Requires platform-provided bool/allocation declarations or a separate wrapper
- Input shape, index and integer-difference preconditions
- Unverified cache-guarantee commentary

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
