# 0912 — Sort an Array

[Problem](https://leetcode.com/problems/sort-an-array/) · [Accepted submission](https://leetcode.com/submissions/detail/2040536510/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 21 / 21 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 21, 2026 09:42**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Build a max-heap in the input array, then repeatedly swap its root into the last active position. Restore the reduced heap with an iterative sift-down after every extraction. The suffix is sorted while the prefix remains a valid heap.

## Complexity

- Time: O(n log n) worst case, with O(n) initial heap construction.
- Auxiliary space / ownership: O(1) auxiliary storage because sift-down is iterative and sorting is in place.

## Assumptions and review notes

Mutates the input and returns the same pointer, so callers must not treat it as an independently allocated output. Heapsort is not stable. Index arithmetic assumes problem-bounded sizes; exercise duplicates, reverse order and one-element arrays.

- Input-backed returned pointer
- In-place unstable sorting
- Heap index arithmetic relies on size bounds

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
