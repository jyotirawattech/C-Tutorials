# 0704 — Binary Search

[Problem](https://leetcode.com/problems/binary-search/) · [Accepted submission](https://leetcode.com/submissions/detail/2040540292/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 47 / 47 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 21, 2026 09:47**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Maintain an inclusive interval that still could contain the target. Compare the midpoint and discard the half whose sorted values cannot match, retaining the midpoint only when it is the answer. Return -1 when the interval becomes empty.

## Complexity

- Time: O(log n) for a sorted array of length n.
- Auxiliary space / ownership: O(1) auxiliary storage.

## Assumptions and review notes

Requires ascending sorted input; with duplicates it returns a matching position rather than necessarily the first. The midpoint formula avoids adding two potentially large indices. Exercise an absent target, endpoint hits and empty input.

- Sorted-input precondition

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
