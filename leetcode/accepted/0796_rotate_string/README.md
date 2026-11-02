# 0796 — Rotate String

[Problem](https://leetcode.com/problems/rotate-string/) · [Accepted submission](https://leetcode.com/submissions/detail/2033710099/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 62 / 62 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 15, 2026 14:23**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Reject unequal lengths, then concatenate the source string with itself. A string of equal length is a rotation exactly when it appears as a substring of that doubled buffer. Free the temporary buffer after the substring test.

## Complexity

- Time: O(n) copying plus substring search; conservative O(n^2) with a naive search, since the C standard does not prescribe strstr's implementation.
- Auxiliary space / ownership: O(n) allocated doubled buffer.

## Assumptions and review notes

Requires valid terminated strings and lengths for which 2*n+1 fits the allocation arithmetic. strcpy is capacity-safe here only because the buffer size is derived from the two lengths; a general adaptation should retain explicit length/bounds checks. Allocation failure returns false, conflating an error with no rotation.

- Unbounded strcpy depends on correctly computed capacity
- String termination and integer-size assumptions

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
