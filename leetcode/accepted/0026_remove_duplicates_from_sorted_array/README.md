# 0026 — Remove Duplicates from Sorted Array

[Problem](https://leetcode.com/problems/remove-duplicates-from-sorted-array/) · [Accepted submission](https://leetcode.com/submissions/detail/2035054515/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 362 / 362 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 16, 2026 16:19**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Keep the last unique value at a slow write position while a fast cursor scans the sorted array. Copy a value forward only when it differs from that last unique value. Return the length of the compacted unique prefix; the suffix is outside the result contract.

## Complexity

- Time: O(n), where n is the input length.
- Auxiliary space / ownership: O(1) auxiliary storage.

## Assumptions and review notes

Requires sorted input and mutates its prefix. Empty input returns zero. Exercise a single repeated run and an already unique array, and use only the returned logical length.

- Sorted-input precondition
- In-place compaction

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
