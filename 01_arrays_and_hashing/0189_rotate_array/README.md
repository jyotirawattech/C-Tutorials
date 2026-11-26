# Rotate Array

Move every element `steps` positions to the right, wrapping at the end.
Rotating `[1, 2, 3, 4, 5]` right by two gives `[4, 5, 1, 2, 3]`.

This is AI-assisted C11 practice for [LeetCode 189](https://leetcode.com/problems/rotate-array/),
dated 26 November 2026. The [archive](../../leetcode/accepted/0189_rotate_array/)
preserves the [original Accepted C submission](https://leetcode.com/submissions/detail/463974219/)
and its displayed submission date. Original practice date and assistance are
unknown. Judge verdict, runtime, memory and Beats for this adaptation are
**Not captured**.

## Three reversals

With `n` elements, moving by `steps` is equivalent to moving by
`r = steps % n`. For `r > 0`, call the first `n - r` elements `A` and the last
`r` elements `B`. The whole-array reversal produces `reverse(B) reverse(A)`.
Reverse those two ranges separately to restore their internal order and get
`B A`. Each range reversal swaps opposite ends until all pairs have been swapped.

`rotateRight(values, count, steps)` changes the caller's array in place and
uses no heap storage. Zero elements is a successful no-op, including with a
NULL pointer. A NULL pointer with a nonzero length or a count whose byte size
would exceed `SIZE_MAX` is rejected before any array access. The caller
supplies `count` writable integers for a valid nonempty input. A zero
remainder leaves the array untouched.

## How much better, and why?

Compare with the **one-position shifts** in the archived C source. Both
variants are compared on a valid input and a nonnegative step count the
archived `int` interface can represent. Let `n` be the number of elements
and `r` the remainder after dividing the step count by `n`.

| Dimension | Archived repeated shifts | Three reversals |
| --- | --- | --- |
| Time, when r > 0 | Θ(nr) | Θ(n) |
| Auxiliary space | O(1) | O(1) |
| Array stores, when r > 0 | n × r | 2 × (floor(n/2) + floor(r/2) + floor((n-r)/2)) |

Every one-position shift writes all `n` slots. A reversal of a range of
length `s` swaps `floor(s/2)` pairs, with two stores per pair. This counts
assignments to array elements in the C code. A zero remainder takes constant
time with no array stores in both versions.

For `n = 10,000` and `r = 5,000`, the model gives 50,000,000 array stores for
shifting and 20,000 for the reversals. Short rotations can favor the baseline.
For `n = 10` and `r = 1`, it uses 10 stores and the reversals use 18. The
store-count advantage depends on the remainder. Paired benchmark **Not run**.
Elapsed-time and process-memory gains are unknown.

## Tests

Run `make test` from the repository root. The local harness checks every
array up to six elements from `{INT_MIN, 0, INT_MAX}` against direct destination
indexing, with step counts through two full rotations and at `SIZE_MAX`.
It also checks invalid arguments and canaries around a rotated subrange.
