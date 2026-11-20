# Merge Two Sorted Lists: check the nodes, not only the values

Public problem: [LeetCode 21](https://leetcode.com/problems/merge-two-sorted-lists/).
This standalone C11 practice relinks two ordered node chains into one ordered
chain. The 20 November 2026 update strengthens the tests and documentation;
the production `mergeTwoLists` function is unchanged from repository revision
`b92f51272fb8ec49ef4065ac5018caff34360ff1`. It is not a new solve.

Original practice date: **Unknown**. Current test/documentation work is
AI-assisted. Exact LeetCode acceptance, matching submission, capture time,
runtime, memory and Beats values for this implementation: **Not captured**.
This practice file is not evidence of an Accepted submission.

## Contract and ownership

Each input is a sorted, acyclic list, possibly empty. The two lists must have
no nodes in common. Nodes stay alive throughout the call, and the caller gives
the function exclusive permission to rewrite their `next` pointers. Unsorted,
cyclic, dangling or overlapping inputs are outside this function's contract.

The returned chain contains precisely the original nodes. Their values do not
change. No node is allocated or freed by `mergeTwoLists`; the caller retains
ownership of the underlying allocations and must eventually release each
allocation once using its matching allocation method. The old heads now refer
into the merged chain, so they must not be treated as independently owned lists.

While both inputs remain, the output prefix is sorted and contains exactly the
nodes already consumed. Its tail points to the last consumed node. Selecting
the smaller head extends that prefix; when one input ends, a single link attaches
the remaining chain. `<=` gives left-list nodes priority on equal values while
preserving each input's order. That cross-list tie choice is tested behavior of
this implementation, not a separate LeetCode requirement.

## How much better, and why?

**Before/after baseline:** the same iterative pointer-splicing function before
this test update. For input lengths `m` and `n`, both versions have worst-case
O(m+n) time, O(1) auxiliary storage and no heap allocation during the merge.
There is no algorithmic performance improvement in this update and no measured
speedup or memory reduction.

**Alternative algorithm:** a conventional recursive pointer merge, choosing
one head and recursively merging the rest, also uses O(m+n) worst-case time
and reuses the input nodes. It can retain O(m+n) call frames; this iterative
sentinel approach uses O(1) working storage. For two nonempty alternating lists
of 20,000 nodes each, either approach can make 39,999 head comparisons; the
recursive approach can have 40,000 simultaneous calls including its base case.
These are algorithmic counts, not elapsed time or measured stack bytes. No
recursive comparator was benchmarked here, and tail-call elimination is not
assumed. The trade-off is explicit pointer mutation and the disjoint-list
ownership contract rather than recursion.

The useful change is the evidence checked. The old harness had three
value-based examples. This harness makes **3,147 merge calls**: ten fixed
fixtures, 3,136 exhaustive short-list pairs and one 40,000-node case. It also
checks that the oracle rejects nine malformed outputs. These finite counts
are not a coverage percentage, proof of correctness or production reliability.

Paired timing/memory benchmark: **Not run**. Measured speedup factor: **null**.
Measured memory reduction percent: **null**.

## What the harness checks

Before merging, the harness records every node's address, value, input origin
and position. It sorts those immutable records by value, then origin and
position with `qsort`, independently of the merge's two-head control flow.
It checks the returned chain against those exact records, then requires NULL
termination after exactly `m+n` nodes. An unexpected pointer is rejected before
it is dereferenced; the checker visits at most `m+n` expected nodes. Thus equal
output values cannot hide a copied, missing, repeated or reordered node, and
value mutation is compared with its original snapshot.

The fixed fixtures retain the original three examples and add the opposite
empty side, duplicates, either tail, `INT_MIN`/`INT_MAX`, unequal lengths and
alternating values. The exhaustive matrix contains all 56 nondecreasing
sequences of lengths zero through five over `{-1, 0, 1}`, paired in both input
positions: 56 x 56 = 3,136 cases. The long fixture alternates two 20,000-node
lists and exercises the unchanged iterative implementation at that stated size.

Nine synthetic outputs separately exercise oracle rejection: missing head,
dropped tail, copied head, foreign head, repeated-node cycle, extra trailing
node, changed value, reversed equal-value origin order and a nonempty result
when zero nodes are expected. These graphs are passed only to the checker;
malformed lists are not passed to `mergeTwoLists`. Fixture allocations are
released by their original allocation handles rather than by following the
rewritten links. Allocation failure in this standalone test harness is an
assertion failure, not a tested production allocation-recovery feature.

The stronger oracle itself uses O(m+n) snapshot storage and a sort. Those test
costs are separate from the merge's O(1) auxiliary-space bound. Assertions are
required; a build with `NDEBUG` is rejected instead of silently skipping checks.

## Run the bounded checks

From this directory:

```bash
clang -Wall -Wextra -Werror -pedantic -std=c11 -g -fno-omit-frame-pointer \
  -fsanitize=undefined -fno-sanitize-recover=all solution.c -o /tmp/merge21-check
UBSAN_OPTIONS=halt_on_error=1 /tmp/merge21-check
```

Actual targeted check on 20 November 2026: strict C11 compilation and fail-fast
UBSan execution passed on macOS using Apple clang version 17.0.0 (clang-1700.0.13.5).

```text
[PASSED] Merge Two Sorted Lists: 10 fixed cases, 3136 exhaustive pairs, 1 long case (40000 nodes), 9 oracle rejection cases.
```

The repository runner uses `make test`; its configured Linux ASan/UBSan and
macOS UBSan jobs are separate checks whose actual public revision and outcome
must be read back after publication. A configured job is not a successful run.
Local ASan was not run because of the previously observed host runtime stall.
This page's targeted run did not invoke a separate leak detector. Finite
assertions and sanitizer success do not establish a universal leak-free or
memory-safe guarantee.
