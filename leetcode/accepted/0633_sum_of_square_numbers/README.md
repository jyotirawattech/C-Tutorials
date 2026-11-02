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

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Enumerate all unordered square-root pairs. For U=floor(sqrt(c)), test every 0<=a<=b<=U.

- Baseline time: O(c) pair-count bound. Space: O(1).
- Submitted approach: Converging two-pointer square-sum search. Time: O(sqrt(c)) for nonnegative c. Space: O(1) auxiliary space.

**How much, by analysis:** The complete baseline has (U+1)(U+2)/2 candidate pairs. The two-pointer loop has at most U+1 iterations because each move narrows the gap by one. This compares worst-case candidate bounds, not an observed time ratio; either method can stop earlier on a match.

**Why:** Monotonic squared sums identify which boundary can move, so one unsuccessful test removes an entire boundary choice.

**Trade-offs and conditions:** Requires nonnegative input, a suitable sqrt bound and widened squared-sum arithmetic. A one-loop search using a square-root test is another O(sqrt(c)) alternative, so the archive is not asymptotically better than every reasonable method.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2040541036/) displayed the following at capture on **2026-11-02T13:49:32.182Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **8.50 MB**; reported memory `Beats`: **54.41%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

The input must be nonnegative. The implementation uses the platform sqrt function to establish its initial bound and long long arithmetic for squared sums; linking may require the math library on some C toolchains.

- No allocation or dangerous library call observed.
- sqrt on invalid negative input is outside the supported contract.
- The source's register-placement wording is not a verified hardware property.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
