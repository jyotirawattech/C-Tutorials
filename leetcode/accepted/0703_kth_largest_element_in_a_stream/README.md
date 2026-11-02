# 0703 — Kth Largest Element in a Stream

[Problem](https://leetcode.com/problems/kth-largest-element-in-a-stream/) · [Accepted submission](https://leetcode.com/submissions/detail/2029347190/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 12 / 12 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 11, 2026 11:27**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Maintain a min-heap containing at most the k largest values observed. Insert while the heap is short; once full, replace its root only when a larger value arrives and restore heap order. When k values are present, the root is the kth largest of all values processed.

## Complexity

- Time: Construction O(n log(k+1)) for n initial values; add O(log(k+1)) worst case and O(1) when a full heap rejects a smaller value
- Auxiliary space / ownership: O(k) stored heap plus O(log(k+1)) recursive helper depth

## Assumptions and review notes

k must be positive and enough values must have arrived before the root represents a kth-largest value. Allocation failure and invalid constructor inputs are not handled in this source.

- Unchecked constructor and heap allocations.
- Invalid k=0 can lead to an out-of-bounds heap[0] access; judged input domain is assumed.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
