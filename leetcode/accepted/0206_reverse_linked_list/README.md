# 0206 — Reverse Linked List

[Problem](https://leetcode.com/problems/reverse-linked-list/) · [Accepted submission](https://leetcode.com/submissions/detail/2033793518/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 28 / 28 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 15, 2026 15:37**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

The submitted primary function saves the next node, redirects the current next pointer toward the reversed prefix, then advances both cursors. That maintains a reversed processed prefix and an untouched remainder until the new head is known. A separately included recursive variant reverses the remainder before redirecting and clearing the original forward edge.

## Complexity

- Time: O(n) for either included variant, where n is list length.
- Auxiliary space / ownership: O(1) auxiliary pointers for reverseList; O(n) recursive call stack for reverseListRecursive.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Recursive list reversal. Reverse the suffix recursively and redirect each original forward link while unwinding.

- Baseline time: O(n). Space: O(n) call stack.
- Submitted approach: Iterative reverseList entry point. Time: O(n). Space: O(1) working pointers; separately included recursive variant uses O(n) stack.

**How much, by analysis:** The primary archived entry avoids up to n recursive frames while still rewiring each of n nodes once. No runtime ratio follows from the stack difference.

**Why:** Saving the next pointer and advancing the reversed prefix replaces recursive state with three pointers.

**Trade-offs and conditions:** The list must be acyclic and mutable. The raw file also contains a recursive alternative, so constant-space claims apply specifically to reverseList, not every function in the file.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2033793518/) displayed the following at capture on **2026-11-02T13:52:02.906Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **11.52 MB**; reported memory `Beats`: **5.14%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Both variants mutate the original list and assume a finite acyclic next chain. The recursive version can exhaust the stack on a sufficiently long list; the comments' production labels are not an independent deployment assessment. Requires the judge-provided ListNode definition.

- Input list mutation
- Recursive alternative has depth risk
- External judge ListNode support type

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
