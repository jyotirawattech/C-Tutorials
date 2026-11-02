# 0482 — License Key Formatting

[Problem](https://leetcode.com/problems/license-key-formatting/) · [Accepted submission](https://leetcode.com/submissions/detail/2033701198/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 40 / 40 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 15, 2026 14:14**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Count non-dash characters to determine the exact formatted length, then fill the output from right to left. Insert a dash after every k retained characters and convert lowercase ASCII letters to uppercase. Backward filling naturally permits the first group to be shorter than the later groups.

## Complexity

- Time: O(n), where n is the input string length.
- Auxiliary space / ownership: O(1) auxiliary state, plus O(n) returned string.

## Assumptions and review notes

Requires a terminated input, k>0, and lengths fitting int. Character conversion assumes ASCII's lowercase-to-uppercase offset; it does not implement locale-aware or Unicode casing. Both result allocations are unchecked, and the caller owns the result.

- Unchecked malloc results
- Positive divisor and ASCII assumptions

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
