# Checked LRU replacement in C

Practice for [LeetCode 146: LRU Cache](https://leetcode.com/problems/lru-cache/), improved on 15 November 2026. This AI-assisted adaptation changes the existing standalone practice API and tests. It is **not a new solve or newly Accepted submission**. The earlier practice example's original authorship, solve date and assistance are **Unknown**. Exact judge acceptance, runtime, memory and Beats for this adaptation: **Not captured**. The separate historical Accepted source and its dates remain unchanged.

The useful question is whether a failed replacement can preserve both cached data and recency. The old example evicted first, then allocated the new list node and hash entry without checking their results. Its `capacity * 2` expression could also overflow a signed int. Its normal successful-operation cleanup already released its nodes, entries, sentinels and table; this change does not claim to repair a baseline normal-path leak.

## Contract and invariant

The checked practice API intentionally differs from the judge's API:

```c
LRUCache *lruCacheCreate(int capacity);
bool lruCachePut(LRUCache *cache, int key, int value);
bool lruCacheGet(LRUCache *cache, int key, int *out);
void lruCacheFree(LRUCache *cache);
```

Keys and values may be any int, including `INT_MIN`, `INT_MAX` and `-1`. A successful get writes `*out` and moves that key to most recently used. A miss, NULL cache or NULL output returns false without changing cache state or output. The output must point to writable caller-owned storage and must not alias cache storage. A put returns false for a NULL cache or allocation failure. Existing-key updates and get operations require no allocations.

Capacity must be in `1..INT_MAX/2`, and the bucket-array byte count must fit `size_t`. Bounds are checked before multiplication or allocation; a representable request can still fail for lack of memory. The bucket count is `B = max(16, 2 * capacity)`. Use only a live cache returned by the constructor; double-free, corrupted/interior pointers and concurrent access are outside this single-threaded example's contract. Defining `LRU_NO_TEST_MAIN` removes the standalone harness. In that mode, paired `LRU_MALLOC`/`LRU_FREE` hooks may be supplied; they must have malloc/free semantics and matching ownership.

Each cached key has exactly one list node and one hash entry pointing to it. The list runs from most recent after `head` to least recent before `tail`; hash buckets use separate chaining. New-key insertion first allocates **both** replacement objects privately. If either allocation fails, it releases any staging allocation and returns before changing values, size, list order or hash links. After both succeed, eviction and insertion have no remaining allocation step. Updating an existing key changes its value and recency directly. Constructor failure releases every successfully allocated component; teardown releases all owned objects iteratively.

## How much improves, and why?

The fair baseline is the [previous standalone LRU implementation at 2ec222a](https://github.com/jyotirawattech/C-Tutorials/blob/2ec222a27d3b46e271f9aafe97802e08f91baa51/05_systems_data_structures/0146_lru_cache/solution.c). Both versions use the same doubly linked list and separate-chaining hash representation. Failure rejection and unambiguous arbitrary-int values are explicit additional requirements here; this comparison does not imply the constrained judge interface required them.

For a full capacity-two cache, the baseline has size **1** when its first replacement allocation is called: eviction has already occurred. The adaptation still has size **2** at that allocation because it has not changed the cache. This is a synthetic operation-order observation with all allocations succeeding, **not** a timing benchmark or a measured crash rate. The baseline's unchecked-failure and signed-overflow risks are source-review findings; no intentional NULL dereference or signed-overflow run is used as evidence.

The harness rejects all four constructor allocation failure positions without retained tracked blocks. It also rejects node and hash-entry allocation failures in a non-full cache, a full cache and a capacity-one cache: **six** put failure cases preserve prior data, structure and recency, with no additional retained tracked blocks. The existing-key/no-allocation case continues to work when the allocator is set to fail. These are exercised cases, not a proof covering every possible program execution.

Let `C` be capacity, `n <= C` live entries and `B` bucket count. Under a suitable distribution of keys, both versions have expected O(1) get/put cost at load `n/B <= 1/2`. Adversarial collisions can make lookup and eviction's hash removal O(C); neither version has a universal constant-time guarantee. List splicing itself is O(1). Constructor initialization is Θ(B), and teardown is Θ(B + n), bounded by Θ(B + C). Live storage is Θ(B + C). There is **no asymptotic speedup** established by this change.

Both versions use **4 + 2n live allocations** in a stable cache: cache, bucket array, two sentinels, and a list node/hash entry per item. The adaptation temporarily needs **two additional allocations** while staging a replacement. In the worked full capacity-two case, eight live blocks temporarily become ten, then return to eight after eviction. Allocation counts are not bytes or RSS. Staging trades that temporary memory for a recoverable failure boundary. No paired elapsed-time benchmark was run; measured speedup and memory/RSS reduction remain **Unknown**.

## Run and check

From the repository root:

```sh
make test
```

Or run this harness alone:

```sh
clang -std=c11 -Wall -Wextra -Werror -pedantic -fsanitize=undefined \
  05_systems_data_structures/0146_lru_cache/solution.c -o /tmp/lru-practice
/tmp/lru-practice
```

Eight groups cover ordinary eviction, all constructor failure positions and invalid capacities, full-int keys/values and unchanged miss/NULL-output state, allocation-free updates/gets, full/non-full put failures, capacity one and collisions, the staging allocation observation, and **12,000 deterministic operations** checked against an independent MRU-array model. The model comparison and structural invariants run after each operation. A large representable capacity is tested with the allocator failing before any large allocation or bucket initialization.

Expected success line:

```text
[PASSED] LRU: 8 groups, 12000 oracle operations, 4 constructor failure positions, 6 put failure cases, zero tracked blocks retained.
```

Allocator counts and assertions establish the exercised behavior, not universal memory safety. Local fail-fast UBSan, full-repository checks and exact-revision hosted CI retain separate evidence. This example claims no local ASan result or new platform verdict, and makes no claim about kernel, TLB or production-cache replacement policies.
