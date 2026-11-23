# 0739 · Daily Temperatures with the stack in the answer array

[Problem](https://leetcode.com/problems/daily-temperatures/) · [Archived submission and provenance](../../leetcode/accepted/0739_daily_temperatures/README.md)

This C11 practice finds the distance to the first strictly warmer future day.
It reuses the answer array while it builds the answer. The practice adaptation
was prepared with AI assistance on 23 November 2026. Its LeetCode verdict,
runtime and memory results are **Not captured**. The archived submission's
original practice date is Unknown.

## Why the links work

Start at day zero and keep a chain of days still waiting for a warmer one.
From newest to oldest, the pending temperatures are nondecreasing. If today's
value is warmer than the head, remove the head and record the distance. Today
is that day's first warmer day because each earlier day has already been checked.
When a head is at least as warm as today, every day deeper in the chain is too.
The scan then adds today to the head. Equal values stay pending.

An unresolved answer slot holds its predecessor's index plus one. Zero ends the
chain. The algorithm reads the next link before overwriting that slot with a
distance. When the scan ends, it walks the remaining chain and writes zeros.
Every slot has its final answer before the function returns.

The input is read only and remains owned by the caller. `daily_temperatures`
returns a status and places the answer in a writable output slot. The caller
frees the answer on success. Empty input succeeds with a null answer. Invalid
arguments or allocation failure leave a provided output slot null. The input
must contain the declared number of `int` elements, the count must fit in `int`,
and the allocation-size calculation must fit in `size_t`.

## Comparison with the archived explicit stack

For `n` input days, both implementations run in O(n) time. Each day is added once
and removed at most once during the scan. The adapted version also finalizes
unresolved days with one last chain walk, so every link is removed exactly once.

The [archived baseline](../../leetcode/accepted/0739_daily_temperatures/submission.c)
requests `n * sizeof(int)` for the output and the same amount for a separate
stack. The adaptation requests only the output allocation for valid nonempty
input. Its auxiliary storage is O(1) excluding input and output, versus O(n)
for the baseline. Both return the same `n`-element answer on valid input when
allocation succeeds.

At 100,000 days with 4-byte `int`, the requested array payload is 800,000 bytes
for the baseline and 400,000 bytes for the adaptation. Reusing the answer slots
removes 400,000 bytes of scratch payload in this model. It also changes the
write pattern, including that final chain walk in place of zero-initializing an
answer array. These figures exclude allocator metadata and fixed local storage.
They describe requested payload, rather than measured RSS or speed. **Paired
benchmark: Not run.**

## Checks

Run `make test` from the repository root. The harness compares 3,280 small inputs
with a direct forward-search oracle, including equal temperatures and both
`int` extremes. An 8,192-day fixture puts thousands of days on the pending chain
before a final spike. The allocation check observes one output allocation and
exercises empty input, an allocation failure and invalid arguments.
