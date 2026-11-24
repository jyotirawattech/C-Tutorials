# Find All Numbers Disappeared in an Array

Given `n` integers from 1 through `n`, return the values that never appear. For
example, `[4, 2, 7, 7, 8, 2, 3, 1]` returns `[5, 6]`. After this call, the input
still holds its original values.

This is AI-assisted C11 practice for [LeetCode 448](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/).
The [original C submission](https://leetcode.com/submissions/detail/2032943655/)
was captured as Accepted and is preserved in the
[separate archive](../../leetcode/accepted/0448_find_all_numbers_disappeared_in_an_array/).
The original practice date and assistance are unknown. The archive preserves the
submission time shown by LeetCode and its capture date. This adaptation is dated
24 November 2026. LeetCode verdict, runtime, memory and Beats for this implementation
are **Not captured**.

## How it works

Check every input value before marking anything. Finding value `v` makes slot
`v - 1` negative if it is still positive. Read the magnitude when visiting a
slot already marked by an earlier value. Each slot turns negative at most once,
so the missing count starts at `n` and drops by one for each distinct value found.

Once all marks are in place, positive slots identify the missing values in
ascending order. Allocate exactly enough space for that list. The final pass
copies missing values and restores negative slots, including when allocation
fails.

`findMissingNumbers(values, count, &result)` requires exclusive, writable access
to the input for the duration of the call. It may temporarily negate elements.
The caller supplies `count` valid int slots and a separate writable `MissingNumbers`
result. A zero-length input can use NULL. The function checks lengths and values,
but C cannot check the extent of a caller's pointer.

On success, `result.count` is the number of missing values and the caller frees
`result.numbers` with `free`. When nothing is missing, the function returns NULL
and a zero count in the result without allocating. Invalid input and allocation
failure return separate statuses and leave the result unchanged.

## How much better, and why?

The baseline is the archived C submission's **sign marking with an n-slot
output buffer**. Compare the two on valid, nonempty inputs with successful
allocation when needed. Let `k` be the number of missing values.

| Dimension | Archived C submission | Restoring practice |
| --- | --- | --- |
| Time | O(n), two array passes | O(n), three passes including validation |
| Auxiliary space | O(1), excluding returned storage | O(1), excluding returned storage |
| Requested output | `n * sizeof(int)` bytes | `k * sizeof(int)` bytes, no allocation at k = 0 |
| Input writes | One sign change per distinct value | One sign change and one restoration per distinct value |

The marked array gives the exact output length before allocation. At
`n = 100,000`, `k = 100` and four-byte ints, the requested output drops from
400,000 bytes to 400 bytes. When every input value is the same, `k = n - 1` and
the saving is only one int. When all values appear, the allocation disappears.
The trade-off is an extra read pass and `n - k` sign restoration writes. The
input contract still requires exclusive access while those marks exist.

The improvement is conditional on `k` and applies to requested output storage.
These are payload and work counts. Paired benchmark **Not run**. Elapsed-time
and process-memory gains are unknown.

## Run the checks

From the repository root, run `make test`. To run this example alone with
fail-fast UBSan:

```sh
build_dir=$(mktemp -d)
clang -std=c11 -Wall -Wextra -Werror -pedantic -fsanitize=undefined \
  -fno-sanitize-recover=all \
  01_arrays_and_hashing/0448_find_all_numbers_disappeared_in_an_array/solution.c \
  -o "$build_dir/missing-numbers"
"$build_dir/missing-numbers"
rm -f "$build_dir/missing-numbers"
rmdir "$build_dir"
```

The harness compares every valid array of length 0 through 6 with a direct
presence scan, checks the exact request size and input values after success,
rejects invalid lengths and values, and injects allocation failure when two
values are missing. Define `MISSING_NUMBERS_NO_TEST_MAIN` to build the practice
function without the harness.

On 24 November 2026, the standalone assertions passed all 50,070 oracle
cases and the invalid-input and allocation-failure checks under fail-fast UBSan.
