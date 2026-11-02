# 1700 — Number of Students Unable to Eat Lunch

[Problem](https://leetcode.com/problems/number-of-students-unable-to-eat-lunch/) · [Accepted submission](https://leetcode.com/submissions/detail/2033035894/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 55 / 55 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 14, 2026 22:17**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Count how many students prefer each sandwich type instead of simulating queue rotations. Process sandwiches in stack order, consuming one matching preference when available. Once no remaining student wants the next sandwich, further rotations cannot help and the remaining counts give the answer.

## Complexity

- Time: O(n + m), for n students and m sandwiches.
- Auxiliary space / ownership: O(1) auxiliary counters.

## Assumptions and review notes

Indexes a two-element array with every preference and sandwich value, so values must be exactly 0 or 1. The intended problem supplies equal-sized arrays; invalid values would index out of bounds. Exercise an immediately blocked sandwich and a sequence all students can consume.

- Direct indexing relies on binary input domain

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
