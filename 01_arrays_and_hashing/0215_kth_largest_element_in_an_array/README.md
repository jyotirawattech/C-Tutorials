# Kth Largest Element in an Array

Find the value at one-based rank `k` when the values are ordered from largest
to smallest. Duplicate values occupy separate ranks. For `[5, 5, 2]`, rank
two gives `5`.

This is AI-assisted C11 practice for [LeetCode 215](https://leetcode.com/problems/kth-largest-element-in-an-array/),
dated 28 November 2026. The [archive](../../leetcode/accepted/0215_kth_largest_element_in_an_array/)
preserves the [original Accepted C submission](https://leetcode.com/submissions/detail/2040535241/)
and its displayed submission date. Original practice date and assistance are
unknown. Judge verdict, runtime, memory and Beats for this adaptation are
**Not captured**.

## Keep the k largest values seen so far

Build a min-heap from the first `k` values, working from the last parent up
to the root. The heap root is the smallest of the retained values. Each
later value at or below the root can be skipped because there are already
`k` values at least as large. A larger value replaces the root. Sift it down
until both children are at least as large as their parent again. The heap
then holds a multiset of the `k` largest values seen, so its root is the
answer after the full scan.

`selectKthLargest(values, count, rank, scratch, capacity, &result)` accepts
readable input, writable scratch storage of at least `rank` ints and a
separate writable result. These regions must be disjoint. The caller
supplies valid storage for both declared extents. The function rejects
NULL pointers, invalid ranks, insufficient scratch and unrepresentable byte
extents before any write. On success it writes the result and the first
`rank` scratch slots. The input and unused scratch are unchanged. It makes
no allocation and uses no random state.

## How much better, and why?

The baseline is the archived C submission's **recursive randomized three-way
quickselect**. Compare on the same valid input and rank. Let `n` be input
length, `k` the rank and `u` the number of heap replacements after
initialization.

| Dimension | Archived quickselect | Read-only heap selection |
| --- | --- | --- |
| Total time | Expected O(n) with suitably distributed pivots, O(n²) worst case | O(n + u log(k + 1)), with u ≤ n − k |
| Auxiliary storage | O(n) worst-case recursion stack, unless calls are optimized away | k caller-provided ints and O(1) additional working space |
| Input effects | Partitions the array in place and reseeds process RNG | Leaves input unchanged, no RNG |

Bottom-up heap construction takes O(k) work. The rest is one scan, with at
most `floor(log2(k))` downward moves per replacement. For the harness's
1,024 increasing integers and `k = 32`, all 992 values after heap construction
replace the root, each with at most five downward moves. The scratch payload
is 32 ints, or 128 bytes with four-byte ints. The original uses no such
array. Its observed time and stack depth on this input are unknown. The
comparison establishes a deterministic work bound and input preservation.
If mutation is acceptable, random pivots can give the archived approach
less work. There is no paired benchmark. Measured time and process-memory
gains are unknown.

## Tests

Run `make test`. The harness checks every rank of every array up to six
elements over `{INT_MIN, 0, INT_MAX}` against a full sort. It also checks
rejected arguments, untouched input and spare scratch, and an increasing
1,024-element input whose rank-32 answer is 992.
