# 0380 — Insert Delete GetRandom O(1)

[Problem](https://leetcode.com/problems/insert-delete-getrandom-o1/) · [Accepted submission](https://leetcode.com/submissions/detail/2029370742/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 21 / 21 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 11, 2026 11:47**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Store live values densely in an array and map each value to its array position with a chained hash table. Removal fills the deleted slot with the last value and repairs that value's recorded index, keeping the array gap-free. Random selection chooses an array index, so selection does not scan the set.

## Complexity

- Time: Expected O(1) insert/remove under well-distributed hashes, O(n) worst-case collision traversal, and O(1) random selection; create O(H) and teardown O(H+n).
- Auxiliary space / ownership: O(C + H + n), for fixed array capacity C=200005, H=100003 hash buckets and n live hash nodes.

## Assumptions and review notes

The array never grows beyond its preallocated capacity, allocations are unchecked, and getRandom requires a nonempty set. rand()%size can introduce modulo bias and uses the process-global generator; it is unsuitable for security-sensitive randomness.

- Fixed array capacity without insertion bound check
- Unchecked allocations
- Modulo bias and empty-set division precondition

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
