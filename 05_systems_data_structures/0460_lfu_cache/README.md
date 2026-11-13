# LFU Cache: checked lifetime and failure-path practice

Problem: [460 — LFU Cache](https://leetcode.com/problems/lfu-cache/).

This C11 adaptation keeps the direct key/frequency tables and per-frequency LRU
lists of the [historical C source](../../leetcode/accepted/0460_lfu_cache/submission.c).
It adds complete cleanup and checked operations that leave visible state unchanged
when resource preparation fails. Empty frequency lists remain allocated until
object destruction, as in the original design.

## Provenance and status

- Historical evidence: [C submission 2029340112](https://leetcode.com/submissions/detail/2029340112/),
  Accepted, displayed 11 June 2026 at 11:21 (timezone unspecified), owned by
  [user0592I](https://leetcode.com/u/user0592I/). Original practice date and
  assistance are Unknown; source was captured on 2 November 2026.
- Historical source SHA-256:
  `e1907a8fba04e303e36c50cb0cd6dfe74ae223a28e4607bad20b2f3f2abf3372`.
  The original source, metadata and date remain unchanged in the 83-entry archive.
- This version: AI-assisted local adaptation and tests, November 2026.
  **LeetCode acceptance and judge runtime/memory: Not captured.** Its checked
  interface differs from the judge interface; it is not an exact accepted source
  or a new solve claim. No unchanged historical implementation is executed here.

## Contract and bounded domain

- `lfuCreate(int capacity)` returns a complete empty object or `NULL`. Capacity
  must be in `0..100005`; invalid capacity or allocation failure returns `NULL`.
- `lfuTryPut(cache, key, value)` returns `true` after a successful insertion or
  existing-value update. New entries start at frequency one. Updating an existing
  key counts as a use: it increases frequency and makes the key newest in that list.
- `lfuTryGet(cache, key, int *value_out)` returns `true`, stores the value and
  records a use on success. Stored negative values, including `-1`, are valid hits.
- A checked operation returns `false` on invalid input, zero capacity, resource
  failure or frequency saturation; get also returns `false` for a missing key or
  `NULL` output. **False never changes visible cache state or writes the output.**
  False therefore reports an unsuccessful operation, rather than only a cache miss.
- `lfuFree(cache)` releases all owned allocations; `lfuFree(NULL)` is allowed.

The fixed tables have **K = 100005 key slots** and **F = 200005 frequency slots**.
Valid integer keys are `0..100004`. Live frequencies are `1..200004`; slot zero is
unused. A get or existing-key put at frequency 200004 is rejected before increment
or indexing, preserving the previous value and recency. This is a bounded LFU
exercise, rather than an unbounded cache. Values may span the C `int` range.

Non-NULL cache pointers must name a live object created by this implementation.
A non-NULL get-output pointer must name writable `int` storage outside the cache's
internal allocations. These range checks cannot validate arbitrary pointers or
concurrent access. The implementation is single-threaded.

## Invariant, ownership and failure atomicity

The key table owns exactly one data node for each live key. Each such node also
appears exactly once in its frequency's doubly linked list. The frequency table
owns each list container and its two sentinel nodes; data-node list links are
aliases. Each list is newest first, making its tail predecessor the least-recent
member. `min_freq` names the smallest nonempty frequency, or zero for an empty cache.

A hit prepares the next frequency list before unlinking the node. All three list
allocations (container, head and tail) must succeed; partial construction releases
its earlier allocations. Only then do frequency, recency and minimum change.
Existing-key put changes the stored value after that successful preparation and
transition. New-key put prepares the data node and any initial list before it can
evict the minimum-frequency, least-recent member. A failed full-cache insertion
therefore preserves the victim and its value and order. No operation can fail
after it begins publishing its prepared transition.

Teardown first scans the owning key table and frees every data node once. It then
scans the frequency table, freeing each retained list's two sentinels and container,
without following the now-stale data-node aliases. Finally it frees the cache.

## Fair baseline, how much changes and trade-offs

Let `N` be live data nodes and `B` the number of allocated frequency lists,
**including empty retained lists**. `B` can exceed `N` and grows with frequency
history, bounded by `F - 1`. Construction initializes the inline tables in
Θ(K + F) work. Both the original design and this adaptation perform O(1) direct
index/list work per valid-domain get/put, with a bounded number of allocations;
allocator latency is outside that operation-count model. Both retain
Θ(K + F + N + B) storage. Checks add branches and allocation preparation; there is
no measured algorithmic speedup or universal latency improvement.

**Named baseline: the historical outer-only destructor body.** The deterministic
teardown test applies that equivalent body to a valid fixture built by this
adaptation: three keys at frequencies one, two and three. The fixture has thirteen
tracked allocations: one cache object, three data nodes and three groups of
list/container/two-sentinel storage. Freeing only the outer object retains
**twelve tracked blocks** (`N + 3B`); complete teardown retains **zero**. Why: the
repair visits the two owning tables and releases all omitted nodes/list storage.
The test separately reclaims every quarantined baseline allocation afterward.

The baseline performs Θ(1) incomplete cleanup; complete cleanup takes
Θ(K + F + N + B) table/ownership work and releases `N + 3B + 1` allocated blocks.
This required extra work fixes lifetime behavior rather than reducing its cost.
It also pays the full table scan for a mostly empty cache. Retaining empty lists
avoids repeated list allocation but retains their storage until teardown.

This is a teardown-only comparison on equivalent adapted fixtures, not a paired
run of the whole historical program. Tracked allocation counts/requested bytes,
RSS, judge snapshots and elapsed time are different quantities. **Paired wall-clock
benchmark: Not run. Measured speedup and process-memory reduction: Unknown.** No
memory-reduction percentage or new judge measurement is inferred.

## Run and inspect the checks

From the repository root:

```sh
make test
```

The runner discovers this directory's `solution.c`. Its seven assertion groups
cover canonical LFU eviction, LRU ties, existing updates, negative values,
capacity/key boundaries, missing/invalid output, the constructor allocation,
all three partial-list failure positions, new-node failure before eviction,
get/update rollback, already-allocated destination lists and frequency saturation.
An independent count/value/last-use model checks **9,000 deterministic operations**
across capacities one, two and four. Structural checks verify node/table/list
aliases, LRU order, the minimum and tracked allocation balance. Boundary saturation
uses an explicitly constructed valid maximum-frequency fixture.

The bounded 32,768-slot test allocator injects `NULL` rather than exhausting host
memory, checks every tracked free and is excluded by `LFU_NO_TEST_MAIN`. With that
define, the core uses ordinary `malloc`/`calloc`/`free`; independent probes may
supply `LFU_MALLOC`, `LFU_CALLOC` and `LFU_FREE` together before inclusion. Run the
assertion harness with assertions enabled. The synthetic checks cover exercised
paths, rather than every possible real out-of-memory condition or caller error.

Focused local Clang C11 syntax/object/link/runtime and core-only compilation
passed on 13 November 2026 with strict warnings and fail-fast UBSan: seven
assertion groups and 9,000 oracle operations. Local ASan was not run because of
the previously documented host runtime stall. Check the [actual workflow results](https://github.com/jyotirawattech/C-Tutorials/actions)
for the exact revision under review. Configured CI, compilation, tracked allocation
balance and exercised sanitizer checks are distinct evidence; none is a universal
correctness or memory-safety guarantee.
