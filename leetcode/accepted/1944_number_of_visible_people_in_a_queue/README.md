# 1944 — Number of Visible People in a Queue

[Problem](https://leetcode.com/problems/number-of-visible-people-in-a-queue/) · [Accepted submission](https://leetcode.com/submissions/detail/2049493001/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 42 / 42 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 29, 2026 08:59**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Sweep from right to left with a monotonic stack of remaining visible height barriers. A new person can see every shorter person popped from the stack, plus the first remaining taller barrier if one exists. Each height enters and leaves the stack at most once.

## Complexity

- Time: O(n), where n is the number of people.
- Auxiliary space / ownership: O(n) auxiliary stack and O(n) returned counts.

## Assumptions and review notes

Uses the problem's distinct-height visibility model and valid nonnegative size. Both allocation failures are checked, but a failure returns NULL while returnSize still contains the requested length; callers must check the pointer. Heap-allocation commentary is not a measured claim about every embedded target's stack limits.

- Requires platform-provided allocation declarations or a separate standard-header wrapper
- Return-size value remains nonzero on allocation failure
- Hardware commentary is not benchmarking evidence

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
