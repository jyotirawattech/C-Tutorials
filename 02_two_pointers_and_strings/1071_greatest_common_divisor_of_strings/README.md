# Greatest Common Divisor of Strings

Given two nonempty byte strings, find the longest block that tiles both. For
example, `ABABAB` and `ABAB` have the common divisor `AB`. The result is a
pointer into the first input and a length.

This is AI-assisted C11 practice for [LeetCode 1071](https://leetcode.com/problems/greatest-common-divisor-of-strings/),
dated 25 November 2026. The separate [archive entry](../../leetcode/accepted/1071_greatest_common_divisor_of_strings/)
preserves the [original Accepted C submission](https://leetcode.com/submissions/detail/2041863308/)
and its displayed submission date. Original practice date and assistance are
unknown. Judge verdict, runtime, memory and Beats for this adaptation are
**Not captured**.

## Why one candidate length is enough

Let `n` and `m` be the two lengths and `d = gcd(n, m)`. The length of any
common divisor must divide both lengths, so it divides `d`. If a shorter block
tiles both strings, the first `d` bytes are a whole number of copies of that
block and therefore tile both strings too. It is enough to check the prefix of
length `d`.

The first `d` bytes already match themselves. Check the rest of the first
string and all of the second, reading the prefix from the beginning each time
a block ends. The prefix offset tracks the next expected byte.

## Calling it

`gcdStringView(first, first_len, second, second_len, &result)` accepts two
readable, nonempty byte spans and a separate writable `StringDivisor` result.
It leaves both inputs unchanged. Embedded NUL is an ordinary byte. C callers
must supply lengths within the actual storage.

A valid call returns `true`. If no block tiles both strings, it sets the view
to `{NULL, 0}`. An empty span or a NULL argument returns `false` and leaves a
provided result unchanged. A matching view borrows storage from the first
input. Keep those bytes alive and unchanged while using the result. Use the
returned length when reading it. Copy the bytes if you need independent ownership
or a NUL-terminated string.

## How much better, and why?

The baseline is the archived C submission's **virtual concatenation and owned
copy**. It compares the two concatenation orders without allocating either one.
The table compares valid nonempty inputs without embedded NUL, using the same
bytes and assuming the baseline's allocation succeeds. For the view, lengths
are already available.

| Dimension | Archived C submission | Borrowed view |
| --- | --- | --- |
| Worst-case time | O(n + m), including length scans and copying | O(n + m), including Euclid's algorithm |
| Auxiliary space | O(1), excluding output | O(1), a pointer and length for the result |
| Result payload on match | One request for d + 1 heap bytes | Zero heap bytes |
| Byte equality checks on match | n + m across both virtual concatenations | n + m - d across the first suffix and second span |

On a mismatch, both scans may stop early. The baseline requests one byte for
its empty string. The view allocates nothing and returns an empty span. For
matching lengths 24,000 and 18,000, the named model gives 42,000 versus 36,000
byte equality checks and 6,001 versus zero requested heap bytes for the result.
If lengths need to be discovered from C strings, that adds a length scan.
The trade-off is the borrowed result's lifetime and length-based API. The
storage advantage applies when the caller can use the view directly.

Paired benchmark **Not run**. Measured timing and process-memory gains are unknown.

## Tests

Run `make test` from the repository root. The standalone harness checks all
15,876 pairs of nonempty binary strings through length six against a descending
divisor search. It also covers embedded NUL, a late mismatch, overlapping read
spans, self-match, and invalid arguments.
