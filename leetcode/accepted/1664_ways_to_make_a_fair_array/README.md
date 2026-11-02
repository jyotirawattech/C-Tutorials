# 1664 — Ways to Make a Fair Array

[Problem](https://leetcode.com/problems/ways-to-make-a-fair-array/) · [Accepted submission](https://leetcode.com/submissions/detail/2040524225/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 105 / 105 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 21, 2026 09:28**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Track even- and odd-index sums on each side of a candidate removal. Remove the current value from the right totals, swap the right side's parity contributions because its indices shift, and compare the resulting even and odd sums. Then add the current value to the left totals before advancing.

## Complexity

- Time: O(n), with one initialization pass and one candidate-removal pass.
- Auxiliary space / ownership: O(1) auxiliary accumulators.

## Assumptions and review notes

Uses long long totals and assumes they can represent the input sums. It leaves the input unchanged. Exercise a single-element array, equal repeated values and removals at each end, where one side has no contribution.

- Accumulator range depends on documented input bounds

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
