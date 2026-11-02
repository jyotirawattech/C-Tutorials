# 0150 — Evaluate Reverse Polish Notation

[Problem](https://leetcode.com/problems/evaluate-reverse-polish-notation/) · [Accepted submission](https://leetcode.com/submissions/detail/2033021128/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 22 / 22 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 14, 2026 22:03**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Scan the tokens while maintaining a stack of completed subexpression values. A one-character operator removes the right operand and then the left operand, computes the operation in that order, and pushes the result. Numeric tokens, including negative numbers, are converted and pushed directly.

## Complexity

- Time: O(t + L), where t is token count and L is the total length of numeric tokens parsed by atoi.
- Auxiliary space / ownership: O(t) auxiliary stack.

## How this solution compares

**Conclusion:** Improvement not established.

**Named baseline:** Conventional operand-stack RPN evaluation. Parse tokens, push numbers and apply operators to the last two operands.

- Baseline time: O(t+L), for token count t and parsed numeric characters L. Space: O(t).
- Submitted approach: Array operand stack. Time: O(t+L). Space: O(t).

**How much, by analysis:** Each token is processed once and each operator performs two operand pops plus one result push in both models. No reduction in growth order or measured speed is established.

**Why:** The archive implements the same stack invariant as the standard baseline; single-character operator recognition keeps negative numbers distinct.

**Trade-offs and conditions:** Valid expressions, nonzero divisors and bounded arithmetic are assumed. atoi and allocation errors are unchecked; contiguous storage does not by itself prove faster execution.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2033021128/) displayed the following at capture on **2026-11-02T13:42:57.229Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **10.43 MB**; reported memory `Beats`: **30.29%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Relies on a valid expression, nonempty tokens, sufficient operands, nonzero divisors, and arithmetic values representable by int. Malformed input can underflow the stack; allocation failures and atoi conversion errors are not handled.

- Unchecked malloc result
- atoi has no conversion/range error reporting
- Division and signed arithmetic rely on validated problem constraints

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
