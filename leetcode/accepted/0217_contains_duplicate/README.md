# 0217 — Contains Duplicate

[Problem](https://leetcode.com/problems/contains-duplicate/) · [Accepted submission](https://leetcode.com/submissions/detail/463988887/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 18 / 18 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Mar 06, 2021 02:18**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Sort the input array and then inspect adjacent elements for equality. Sorting groups equal values together, so any duplicate must appear in an adjacent pair. The first such pair returns true; reaching the end establishes no duplicate under the sorting contract.

## Complexity

- Time: O(n log n) if the platform qsort implementation provides that sorting bound; final scan O(n). The C standard does not prescribe qsort's worst-case complexity.
- Auxiliary space / ownership: Sorting workspace is implementation-dependent; the explicit adjacent scan uses O(1) state

## Assumptions and review notes

qsort mutates the input. The comparator subtracts two ints, which can overflow outside the problem's bounded value range; this fragment also relies on judge-supplied declarations for bool and qsort.

- Comparator subtraction can have signed overflow on arbitrary full-range int inputs.
- Missing stdlib.h/stdbool.h includes make this a judge fragment rather than a standalone C translation unit.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
