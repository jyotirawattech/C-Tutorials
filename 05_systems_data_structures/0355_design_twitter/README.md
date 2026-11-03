# 355 — Design Twitter: corrected local practice

[Problem](https://leetcode.com/problems/design-twitter/) ·
[Historical source and receipt](../../leetcode/accepted/0355_design_twitter/README.md) ·
[Historical counterexample](../../leetcode/review/README.md)

Adaptation date: **3 November 2026**. Original practice date/assistance: Unknown.
This implementation and its tests were prepared with AI assistance from the
archived C source and a synthetic regression. **Platform acceptance for this
changed implementation: Not captured.** It was not submitted to LeetCode and is
not another accepted solve. The original source, hash and June submission date
remain unchanged.

## Task and contract

Keep each author's posts and follow relationships; return at most ten included
post IDs, newest first. This is an in-memory, single-threaded practice exercise
with user IDs 1..500. It performs no network, account or filesystem operation.

The adaptation's post/follow/unfollow functions return `bool` for rejected inputs;
the judge's corresponding API uses `void`. It is therefore not presented as an
unchanged drop-in submission. Self-follow/unfollow is an idempotent no-op, and
your own posts are always included. A feed's allocated array belongs to its
caller. A NULL feed with size zero can mean empty, invalid input or allocation
failure; applications needing distinct reasons should use an explicit error type.

## What failed, and what changed

The old ten **left-to-right** bubble passes can leave newer posts outside the
returned prefix. After users 1, 2 and 3 each post ten times in that order, user 1
following both others should see IDs 309..300. The preserved historical code
returns 209..200 on that synthetic case.

The adaptation scans **right to left** on each pass. After pass `i`, positions
0..i contain the newest i+1 candidates in order: each pass moves the maximum of
the remaining suffix into position i. Stop after ten prefix positions are settled.

Ten retained posts per included author are sufficient: a discarded older post
already has ten newer included posts from that same author, so it cannot enter
the global top ten. Ring counts remain bounded by ten and slot indices by nine;
they no longer grow indefinitely. A 64-bit sequence counter rejects a post before
exhaustion rather than wrapping. All object/ID/output-pointer checks precede
indexing, allocation results are checked, and rejected posts do not mutate state.

## How much better, and why?

Let U=500 candidate authors, F be included authors, T<=10F gathered tweets and
K=10 the output limit. Posting/following/unfollowing take O(1). Object creation
and storage are O(U²+UK) for the zeroed follow matrix and rings. Feed collection
takes O(U+T); the corrected ordering takes O(KT), for O(U+KT) total. The feed reserves O(UK) working storage even when only T
candidates are populated,
plus O(K) caller-owned output. Its fixed U*K candidate array is on the stack, so
this is not an unbounded-user design.

**Fair performance baseline:** a correct, full descending bubble sort of the same
candidates, using the same data layout and fixed passes without early exits.
Its feed ordering costs O(T²), with the same O(UK) allocated working storage. Full sorting does
T(T-1)/2 timestamp comparisons. The adaptation does
P*T-P(P+1)/2, where P=min(K,max(T-1,0)).

For T=30, those counts are **435 versus 245 comparisons**: 190 fewer, or about
43.7% fewer in this particular operation model. The saving comes from settling
only the required prefix. This is a derived comparison count, **not a measured
elapsed-time speedup**. At T<=11 the comparison counts are equal; there is no
universal improvement. Relative to the defective historical partial sort, the
comparison count is unchanged: the demonstrated benefit is **correct output**.

A heap merge of per-author streams is a stronger scaling alternative: after
collecting stream heads it can use O(F+K log(F+1)) heap work and O(F) heap storage,
alongside author discovery. This bounded partial-sort exercise does not claim to
beat it. The wider timestamp and guards also add costs relative to the historical
code; no memory saving or globally fastest solution is claimed.

Verdict: **correctness repair; conditional comparison-count reduction against the
named full-sort baseline.** Paired timing/memory benchmark: **Not run**. Measured
speedup factor and measured memory-reduction percentage: **null**. Judge runtime,
memory, Beats and matching changed-code acceptance receipt: **Not captured**.
The historical source's displayed measurements do not transfer to this code.

## Reproducible checks

From the repository root:

```sh
make test
make test-accepted
make test-comparisons
```

`make test` discovers the new `solution.c` alongside the existing twelve harnesses.
This harness exercises the 30-tweet counterexample; empty and one/two-user feeds;
follow/unfollow, repeats and self-follow; 25-post ring wraparound; all 500 users
and 5,000 retained candidates; invalid/null inputs; and timestamp exhaustion.
It also checks feeds through 2,048 deterministic mixed operations against an
independent oracle that retains the complete global post history and scans it
newest first. The oracle does not share the ring-buffer or sorting implementation.

Local validation on 3 November 2026 uses strict C11 warnings and fail-fast UBSan.
All thirteen practice harnesses, six runner regressions and twenty Python
integrity/comparison tests passed. Thirteen separate Apple `leaks` invocations
returned zero with restricted-process notices retained; this is bounded detector
evidence. All 83 source integrity/object-compilation checks and 83 comparison
records passed. The original counterexample was reproduced separately; replacing
the corrected pass with the old direction made the new harness fail as expected. Local ASan is not run because
the host's runtime previously stalled; Linux CI runs the configured ASan+UBSan
mode. Allocation failures are handled in code but not fault-injected by this
committed harness. Exercised cases and sanitizer checks are bounded evidence,
not proof for every input or a universal memory-safety guarantee.
