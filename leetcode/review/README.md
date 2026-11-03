# Archive review notes

This collection preserves historical accepted submissions, rather than silently
replacing them with new implementations. Each source has a problem/submission
receipt, export hash and original displayed timestamp. Explanatory notes were
prepared through static source review with AI assistance.

Platform Accepted, successful object compilation, runtime tests and memory-safety
checks establish different things. `make test-accepted` verifies all 83 archive
identities/hashes and compiles sources independently with explicit LeetCode support
declarations. It does not execute every archived algorithm. `make test` exercises
the thirteen standalone practice examples and the integrity/runner regression gates.
Original code comments are retained as historical text, not independent benchmarks.

## Reproduced feed-order issue: 355, Design Twitter

The [archived submission](../accepted/0355_design_twitter/README.md) has a historical
Accepted receipt. A later synthetic regression demonstrates an ordering defect:

1. Users 1, 2 and 3 each post ten tweets, in that order, using IDs 100–109,
   200–209 and 300–309.
2. User 1 follows users 2 and 3, then requests the ten newest tweets.
3. The expected feed is 309 through 300; this archived implementation returns
   209 through 200.

The feed collector performs only ten left-to-right bubble-sort passes. A later
tweet can move toward the front only one position per pass, so newer candidates
can remain outside the returned prefix. The source remains unchanged and the
historical platform result is not rewritten.

Run the [synthetic reproduction](0355_feed_order.c) from the repository root:

```sh
clang -std=c11 -fsanitize=undefined -fno-sanitize-recover=all \
  leetcode/review/0355_feed_order.c -o /tmp/0355_feed_order
/tmp/0355_feed_order
```

Exit zero means this exact known counterexample was reproduced, **not** that the
archived feed algorithm is correct. A changed outcome requires review. This case
was reproduced locally with fail-fast UBSan on 2 November 2026; it is not broad
behavioral coverage of the remaining archive.

A separately labelled [corrected local adaptation](../../05_systems_data_structures/0355_design_twitter/README.md)
was added on 3 November 2026. Right-to-left partial passes settle the newest
prefix; its tests include this counterexample and an independent full-history
oracle. It does not replace the archived source or inherit its Accepted verdict
or performance displays. See that entry for the comparison model and actual
validation limits.

## Ownership and input-bound limitations

Static review found incomplete populated-object teardown in [432, All O`one](../accepted/0432_all_oone_data_structure/README.md)
and [460, LFU Cache](../accepted/0460_lfu_cache/README.md). Allocation-failure cleanup
is incomplete in some paths of [932, Beautiful Array](../accepted/0932_beautiful_array/README.md)
and [3756, Concatenate Non-Zero Digits II](../accepted/3756_concatenate_non_zero_digits_and_multiply_by_sum_ii/README.md).
These are source-review observations, not claims that all normal judge inputs fail.

Other entries document their actual constraints, returned-pointer ownership,
unchecked allocations, input mutation or arithmetic assumptions beside the code.
Historical Accepted is not a guarantee of correct behavior for every input,
complete cleanup, allocation-failure handling or measured hardware performance.
Any future corrected implementation should be labelled separately and tested;
it must not be presented as the unchanged historical submission.
