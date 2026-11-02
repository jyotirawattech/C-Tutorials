# 0932 — Beautiful Array

[Problem](https://leetcode.com/problems/beautiful-array/) · [Accepted submission](https://leetcode.com/submissions/detail/2041563723/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 38 / 38 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 22, 2026 09:19**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Start with [1] and repeatedly map the current order to all allowed odd values, followed by all allowed even values. Each affine mapping preserves the absence of an arithmetic-progression midpoint within a half, and opposite parity prevents such a midpoint across the halves. Filter values above n and repeat until the permutation has n entries.

## Complexity

- Time: O(n), since successive array lengths double until reaching n and their total work is a geometric sum.
- Auxiliary space / ownership: O(n) auxiliary temporary buffer plus O(n) returned array.

## Assumptions and review notes

Requires n>=1 and problem-bounded multiplication by two. If just one of the two allocations fails, the other successful allocation is leaked before returning NULL. The caller must free the returned array; test n=1 and non-powers of two.

- Known partial-allocation failure leak
- Positive-size precondition

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
