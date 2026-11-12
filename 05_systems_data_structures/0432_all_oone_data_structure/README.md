# All O`one: ownership and allocation-failure practice

This C11 adaptation keeps the hash index and ordered frequency buckets of the
[historical C source](../../leetcode/accepted/0432_all_oone_data_structure/submission.c).
It repairs object lifetime and allocation-failure paths, with checked operations
that report failure. It is separate from the preserved Accepted source.

## Provenance and status

- Historical evidence: [submission 2029540776](https://leetcode.com/submissions/detail/2029540776/),
  C, Accepted, displayed 11 June 2026 at 14:39 (timezone unspecified), owned by
  [user0592I](https://leetcode.com/u/user0592I/). Original practice date and
  assistance are Unknown.
- Historical source SHA-256:
  `ecbc4bbc360c6b716974a5ae539f995792f798f156453ee0e1fb887146528777`.
  That source and its date are unchanged in the 83-entry archive.
- This version: AI-assisted local adaptation and tests, November 2026.
  **LeetCode acceptance and judge runtime/memory: Not captured.** The checked
  `bool` interface differs from the platform's `void` update interface; this is
  not an exact accepted submission or a new solve claim.

## Ownership and transition invariant

Each live key node belongs to exactly one nonempty frequency bucket. Real
buckets have strictly increasing positive counts between two sentinels. A node's
bucket pointer and neighboring key pointers agree with that owning bucket. The
hash table aliases those nodes; it never owns a second copy of a key.

Increment/decrement uses the adjacent count bucket, creating it only when absent.
All allocations needed for an operation complete before the existing node is
unlinked or a new node becomes visible in either index. Allocation failure leaves
counts, links and visible keys unchanged. A failed new-key bucket allocation frees
the detached node. Constructor failure releases every earlier allocation.

`allOneFree` walks each owning bucket's key list, frees its nodes once, then frees
the bucket. It finally frees both sentinels, the alias table and the object. It
does not follow hash aliases while releasing nodes.

## Interface and input boundary

- `allOneCreate()` returns a complete empty object or `NULL`.
- `allOneTryInc(obj, key)` returns `false` for invalid input, allocation failure,
  or a count already at `INT_MAX`.
- `allOneTryDec(obj, key)` returns `false` for invalid input, a missing key or
  allocation failure. Decrementing count one deletes the key.
- `allOneGetMinKey` / `allOneGetMaxKey` return a borrowed read-only key; ties may
  return any qualifying key. Empty or `NULL` objects return `""`. Do not free
  the result; consume or copy it before the next mutation or object destruction.
- `allOneFree(NULL)` is allowed. Other non-NULL object pointers must refer to a
  live object created by this implementation.

Keys must be valid NUL-terminated C strings of **1–10 lowercase ASCII letters**.
The bounded validation rejects empty, overlong and out-of-domain keys; copying
uses the validated length, including the terminator. Validation cannot make an
invalid or undersized memory pointer safe. This is single-threaded practice,
without synchronization or arbitrary-pointer validation.

## Complexity and fair comparison

Let `H = 100003` table slots, `K` live keys and `B` real frequency buckets, with
`B <= K`. Keys have at most ten characters.

Construction initializes the table in Θ(H) time and uses Θ(H) space. Hash lookup
is expected O(1) at a bounded load with adequately dispersed hashes; its worst
case is O(K) with collisions. A successful update performs O(1) bucket/link work
after lookup and may allocate at most one bucket (plus one node for a new key).
Extrema access is O(1), returning a borrowed pointer. Total owned storage is
Θ(H + K + B). These are the same indexing and storage bounds as the original
design, rather than a claimed algorithmic speedup.

**Named baseline: the historical four-free destructor body.** The test applies
that equivalent body to a valid fixture built by this adaptation: three live
keys at counts one, two and three. Before teardown it has ten tracked allocations:
four infrastructure blocks, three nodes and three real buckets. The baseline
releases only the four infrastructure blocks and retains **six blocks**. The
repaired destructor retains **zero** on the identical fixture. Why: it follows
the owning bucket lists and visits the six previously omitted allocations. The
test explicitly cleans up the baseline's quarantined allocations afterward.

For a general live fixture, the baseline omits `K + B` allocations. Complete
teardown takes Θ(K + B) time and `K + B + 4` frees, trading additional required
cleanup work for correct lifetime handling. This comparison executes only the
equivalent teardown body on an adapted fixture; it does not execute the entire
historical algorithm or establish a full-program memory reduction percentage.
Requested allocation bytes, retained blocks, RSS and elapsed time are different
quantities. **Paired wall-clock benchmark: Not run. Measured speedup and process
memory reduction: Unknown.** Allocation checks add branches; no universal memory
or latency improvement is claimed. Synthetic failure tests establish the tested
failure behavior, not success under every real out-of-memory condition.

## Run and inspect the evidence

From the repository root:

```sh
make test
```

The runner discovers this directory's `solution.c`. Its six assertion groups
cover empty state, ties, updates/deletion, three colliding keys, key/count
boundaries, each constructor allocation failure, new-key partial allocation
failure, increment/decrement target-bucket failure and existing-bucket moves.
An independent count-map oracle checks 8,000 deterministic synthetic operations;
structural assertions check ownership and hash aliases, and tracked teardown
checks outstanding allocations. The fixed 256-slot fault allocator is test-only;
it injects `NULL` results without exhausting host memory and checks every tracked
free. Tests must run with assertions enabled.

To compile the core without the test allocator or test `main`, define
`ALLONE_NO_TEST_MAIN`; it then uses ordinary `malloc`, `calloc` and `free`.

The focused local Clang C11 build, executable and core-only compile passed with
strict warnings and fail-fast UBSan on 12 November 2026. Local ASan was not run
because of the previously documented host runtime stall. Check the
[actual CI results](https://github.com/jyotirawattech/C-Tutorials/actions) for the
revision under review; a configured workflow is not a completed run. Tracked
allocation balance and exercised sanitizer checks are bounded evidence, not a
proof of correctness or memory safety for all callers.
