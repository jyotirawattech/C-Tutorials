# 0232 — Implement Queue using Stacks

[Problem](https://leetcode.com/problems/implement-queue-using-stacks/) · [Accepted submission](https://leetcode.com/submissions/detail/2033038568/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 23 / 23 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 14, 2026 22:20**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Push new elements onto an input stack and remove elements from an output stack. Transfer the entire input stack only when the output stack is empty, reversing the order so the oldest queued value is next. Each element moves between stacks at most once before removal.

## Complexity

- Time: Push and empty are O(1); pop and peek are amortized O(1), with O(k) for an individual transfer of k queued elements.
- Auxiliary space / ownership: Two fixed arrays of 100 integers, O(1) for the implemented capacity; a scalable form would use O(q) for queue capacity q.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Array queue with shift-on-pop. Keep queue order in an array and shift every remaining value after removing the front.

- Baseline time: O(1) push and O(q) pop at queue length q. Space: O(q) capacity.
- Submitted approach: Lazy two-stack queue. Time: Amortized O(1) push/pop/peek; an individual transfer is O(q). Space: Two fixed 100-element arrays.

**How much, by analysis:** Popping q queued items can shift q(q-1)/2 values in the baseline. The archived transfer moves each of those q values between stacks once, followed by q output pops; these operation counts are not an elapsed ratio.

**Why:** Each value moves to the output stack at most once instead of being shifted after every earlier removal.

**Trade-offs and conditions:** Worst-case latency for one operation is still linear. Fixed capacity, nonempty pop/peek calls and successful construction are assumed; it is not an unbounded queue.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2033038568/) displayed the following at capture on **2026-11-02T13:42:02.613Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **9.00 MB**; reported memory `Beats`: **89.60%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

The submitted implementation assumes the platform's operation/capacity bounds and valid nonempty pop/peek calls. It does not grow the fixed arrays or handle allocation failure; repeated pushes beyond the allowed capacity would write out of bounds.

- Fixed-capacity stacks without overflow checks
- Empty pop/peek unchecked
- Unchecked malloc result

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
