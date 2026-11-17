# Valid Parentheses: a checked C span API

This adaptation validates a bounded byte span containing three bracket types.
An empty span is valid. A nonempty span is valid only when every opening bracket
has the right closing bracket in nesting order. See
[LeetCode 20](https://leetcode.com/problems/valid-parentheses/) for the related
judge problem; this checked API intentionally has its own contract.

    typedef enum {
        BRACKETS_VALID, BRACKETS_INVALID, BRACKETS_INVALID_ARGUMENT,
        BRACKETS_ALLOCATION_FAILURE
    } BracketStatus;

    BracketStatus validateBracketsChecked(const char *data, size_t length);

**Contract:** the caller supplies exactly length readable bytes. NULL is allowed
only for an empty span. No terminator is required, embedded NUL is invalid
content, and bytes after the span are ignored. The function borrows the input and
does not modify it. C cannot verify a pointer's readability or its allocation
extent, so a false length is a caller error.

Empty and odd lengths need no stack allocation. A positive even length uses one
allocation; failure returns **BRACKETS_ALLOCATION_FAILURE** before bracket content
can be classified. A NULL pointer with a nonzero length returns
**BRACKETS_INVALID_ARGUMENT**. Other unsuccessful classifications return
**BRACKETS_INVALID**. This separates operational failure from invalid syntax.

## Invariant and half-length stack

The stack stores expected closing brackets for the unmatched opening brackets
already scanned, with the most recent expectation on top. Matching a closer
pops one expectation; a mismatched closer, an empty-stack closer or a non-bracket
byte rejects the span. Successful completion requires an empty stack.

For even input length n, every valid sequence has exactly n/2 opening brackets.
Its pending depth therefore cannot exceed n/2. The implementation allocates n/2
C bytes and rejects before a push would exceed that bound. Such a prefix cannot
belong to any valid sequence of this total length. Stack indices and depth use
size_t, and division avoids multiplication overflow. Every successful allocation
is released on the common return path, including malformed inputs.

## How much better, and why?

The named baseline is the previous
[standalone implementation at d5cee4a](https://github.com/jyotirawattech/C-Tutorials/blob/d5cee4a406e0c491ee51f062318e975fa7a3282f/02_two_pointers_and_strings/0020_valid_parentheses/solution.c)
(source SHA-256
6fabc9ec7a6d01d23b37e461a48abf80a1c8a1756bdabbf1287dba8c5cb8ed3c).
It accepts a C string, measures its length, allocates n stack bytes and returns a
boolean. The checked implementation accepts an explicit span and returns a status.

For the same nonempty even bracket input of n bytes:

- Both use O(n) worst-case time, O(n) auxiliary space and one stack allocation.
- Requested stack **payload** falls from n to n/2 C bytes. On the six-byte input
  **([{}])**, that is **6 to 3 bytes**, a 50% reduction in requested stack payload.
  This says nothing about allocator overhead, size classes, RSS or total memory.
- Both still perform the same LIFO matching work. The new capacity check can
  reject an already impossible excess-opening prefix without overflowing depth.
- Empty input now makes zero allocation attempts. The baseline attempts
  malloc(0), whose permitted NULL result causes it to return false. A controlled
  allocator fixture demonstrates that boundary, and a nonempty allocation
  failure now has a distinct result. These are reusable-API improvements, not a
  claim that the historical judge-domain Accepted source was disproved.

The previous odd-length guard followed a full length scan, so that whole path
was O(n), not O(1). Given a known length, the new odd-length guard is O(1).
Obtaining that length from a C string still requires its own O(n) scan; the API
change does not establish a free runtime improvement.

**Trade-offs:** callers must provide a truthful readable span and handle four
statuses. An even invalid span may encounter allocation failure before its
syntax is determined. The algorithm remains a heap-allocating stack validator;
it is neither allocation-free nor a parser for arbitrary programming languages.

**Paired wall-clock/RSS benchmark: not run.** No measured runtime, throughput,
total-memory or production-safety gain is claimed.

## Reproduce the bounded checks

From this directory:

    clang -std=c11 -Wall -Wextra -Werror -pedantic \
      -fsanitize=undefined -fno-sanitize-recover=all \
      solution.c -o /tmp/brackets-checked
    /tmp/brackets-checked

The embedded harness covers fixed syntax, explicit-span/NULL/empty boundaries,
four injected allocation failures, a short-input independent grammar oracle,
seeded oracle cases, 100,000-level nesting and early rejection, plus 256 byte
values in a two-byte input. Input preservation and tracked allocation ownership
are asserted. These are bounded checks, not a general leak or memory-safety proof.

For reuse or an independent harness, define **BRACKETS_NO_TEST_MAIN** to exclude
the embedded tests. Optionally supply both **BRACKETS_MALLOC** and
**BRACKETS_FREE** with matching malloc/free ownership semantics. With neither hook,
that build uses the standard allocator. Local ASan is not part of the command
above; hosted Linux ASan/UBSan and macOS UBSan are separate CI evidence.

## Provenance and status

- Original standalone practice date and assistance: **Unknown**.
- This checked adaptation and its explanation/tests: **AI-assisted, 17 November 2026**.
- Exact LeetCode verdict, runtime, memory and Beats values for this changed API:
  **Not captured**. No submission was made to obtain them.
- Original historical Accepted problem-20 source, metadata and submission date
  remain unchanged in the separate archive. This is an existing-practice
  improvement, not another solved identity.
- Inputs are generic synthetic brackets and bytes. No private conversation,
  employer/customer code, assessment prompt, editorial or full statement is used.
