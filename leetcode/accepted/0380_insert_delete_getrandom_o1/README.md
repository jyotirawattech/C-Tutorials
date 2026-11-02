# 0380 — Insert Delete GetRandom O(1)

[Problem](https://leetcode.com/problems/insert-delete-getrandom-o1/) · [Accepted submission](https://leetcode.com/submissions/detail/2029370742/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 21 / 21 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 11, 2026 11:47**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Store live values densely in an array and map each value to its array position with a chained hash table. Removal fills the deleted slot with the last value and repairs that value's recorded index, keeping the array gap-free. Random selection chooses an array index, so selection does not scan the set.

## Complexity

- Time: Expected O(1) insert/remove under well-distributed hashes, O(n) worst-case collision traversal, and O(1) random selection; create O(H) and teardown O(H+n).
- Auxiliary space / ownership: O(C + H + n), for fixed array capacity C=200005, H=100003 hash buckets and n live hash nodes.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Dense array with linear membership search. Scan the array to find or reject a value; remove by swapping the last element; select a random index.

- Baseline time: O(n) insert/remove membership checks, O(1) random lookup. Space: O(n).
- Submitted approach: Dense array plus chained hash index. Time: Expected O(1) insert/remove, worst O(n) collision search; O(1) random lookup. Space: O(C+H+n), C=200005 and H=100003.

**How much, by analysis:** The baseline may inspect n values per membership operation; the archive expects a short hash chain but can still inspect n nodes under collisions. No faster-percentage or worst-case constant-time claim is justified.

**Why:** The hash table finds a value's array slot without a full membership scan, and swap-and-pop keeps random lookup dense.

**Trade-offs and conditions:** Large fixed buffers/init costs may lose for small sets; capacity and allocations are unchecked. rand()%size requires a nonempty set and can introduce modulo bias rather than exact uniformity.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2029370742/) displayed the following at capture on **2026-11-02T13:45:34.916Z**:

- Runtime: **35 ms**; reported runtime `Beats`: **96.48%**.
- Memory: **95.14 MB**; reported memory `Beats`: **45.07%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

The array never grows beyond its preallocated capacity, allocations are unchecked, and getRandom requires a nonempty set. rand()%size can introduce modulo bias and uses the process-global generator; it is unsuitable for security-sensitive randomness.

- Fixed array capacity without insertion bound check
- Unchecked allocations
- Modulo bias and empty-set division precondition

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
