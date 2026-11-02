# 0633 — Sum of Square Numbers

[Problem](https://leetcode.com/problems/sum-of-square-numbers/) · [Accepted submission](https://leetcode.com/submissions/detail/2040541036/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 127 / 127 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 21, 2026 09:48**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Start candidate square roots at zero and floor(sqrt(c)). If their squared sum is too small, increase the lower value; if too large, decrease the upper value. Monotonicity of squaring nonnegative integers lets each move discard impossible pairs.

## Complexity

- Time: O(sqrt(c)) for nonnegative c
- Auxiliary space / ownership: O(1) auxiliary space

## Assumptions and review notes

The input must be nonnegative. The implementation uses the platform sqrt function to establish its initial bound and long long arithmetic for squared sums; linking may require the math library on some C toolchains.

- No allocation or dangerous library call observed.
- sqrt on invalid negative input is outside the supported contract.
- The source's register-placement wording is not a verified hardware property.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
