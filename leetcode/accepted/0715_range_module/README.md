# 0715 — Range Module

[Problem](https://leetcode.com/problems/range-module/) · [Accepted submission](https://leetcode.com/submissions/detail/2029644041/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 56 / 56 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 11, 2026 16:22**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Represent tracked integer segments with a dynamic segment-tree layout over the fixed coordinate range 1..10^9. Lazy assignment marks an entire covered segment as added or removed; partial operations propagate that assignment to children. Query combines coverage with logical AND, while public half-open intervals are converted to inclusive endpoints using right-1.

## Complexity

- Time: O(log R) per contiguous range update/query, where R=10^9 coordinate span; construction initializes a fixed pool of P=400000 nodes
- Auxiliary space / ownership: O(P) preallocated node pool plus O(log R) recursion depth

## Assumptions and review notes

The implementation grows indices inside a fixed 400000-node pool without checking capacity. Allocation failure, invalid intervals or sufficiently many node creations can produce invalid accesses; the historical Accepted result is not a general capacity-safety guarantee.

- Unchecked RangeModule/tree allocations.
- Unchecked node_count growth when children are created, including propagation during queries.
- The fixed valid coordinate/left<right domain is assumed.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
