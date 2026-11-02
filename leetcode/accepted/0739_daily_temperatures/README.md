# 0739 — Daily Temperatures

[Problem](https://leetcode.com/problems/daily-temperatures/) · [Accepted submission](https://leetcode.com/submissions/detail/2033029335/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 48 / 48 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 14, 2026 22:11**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Keep a stack of indices whose next warmer day is unresolved, in nonincreasing temperature order. A warmer current day resolves and pops all colder indices at the top, recording their distance from the current index. Indices still on the stack at the end retain the zero initialized answer.

## Complexity

- Time: O(n) amortized, because every index is pushed once and popped at most once
- Auxiliary space / ownership: O(n) auxiliary stack and O(n) returned result

## Assumptions and review notes

Equal temperatures must remain unresolved until a strictly warmer day appears. The archived source does not check either allocation before use; callers own the returned answer array.

- Unchecked calloc/malloc results.
- Input and returnSize pointers are assumed valid within the judged contract.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
