# Checked trie insertion in C

Practice for [LeetCode 208: Implement Trie](https://leetcode.com/problems/implement-trie-prefix-tree/), improved on 14 November 2026. This is an AI-assisted, locally tested adaptation of the existing standalone example, not a new solve or a newly Accepted submission. The earlier example's original solve date, authorship and assistance are **Unknown**. Judge acceptance, runtime, memory and Beats for this adaptation: **Not captured**. The separate historical Accepted archive is unchanged.

The useful question is what happens when an insertion contains an invalid byte or runs out of memory. The previous example silently skipped invalid characters and attached newly allocated nodes immediately. Thus `ab#c` could insert `abc`; a failed allocation could leave a partial path and then dereference NULL.

## Contract and invariant

Pass the owning root returned by `trieCreate()` and readable NUL-terminated C strings. Keys contain only lowercase ASCII `a` through `z`; reject a whole invalid key, including high bytes, without normalization or mutation. NULL roots/strings fail. Empty strings are supported: an empty prefix is true for any live root, and an empty word becomes searchable after its insertion.

`bool trieInsert(Trie *, const char *)` returns false for invalid input or allocation failure. This checked return is an intentional practice API change from the old void insertion. Duplicate words and words whose paths already exist require no allocation.

Each child edge represents its exact next character. Terminal flags mark complete inserted words. The root's `owned_next` chain owns every other node exactly once. Insertion validates the entire input, follows existing edges, then builds any missing suffix privately. If an allocation fails, it frees that detached chain. Only after every allocation succeeds does it attach the suffix and transfer ownership. Existing query results and structural links therefore survive a failed insertion unchanged. Operations are single-threaded; the commit is not a concurrency primitive. Do not pass interior nodes as owning roots or modify links from outside the implementation.

`trieFree()` walks the allocation chain iteratively, so teardown and rollback do not recurse through a potentially deep tree. The allocator hooks must be supplied as a matching pair. The default standalone harness tracks allocations and injects failures; defining `TRIE_NO_TEST_MAIN` removes that harness and uses ordinary malloc/free unless hooks are overridden. This is a lowercase string trie, not an IP longest-prefix-match implementation or a production routing table.

## How much improves, and why?

The fair baseline is this repository's [previous standalone 208 implementation at a66f634](https://github.com/jyotirawattech/C-Tutorials/blob/a66f63409149b192686e6f92ea775746fa4dc347/04_trees_and_graphs/0208_implement_trie/solution.c), using the same lowercase character representation and successful-operation task. Invalid-input behavior and allocation-failure handling are additional explicit requirements in the adaptation; the comparison does not imply that LeetCode's constrained tests require them.

Let `L` be the input length, `k <= L` the missing suffix length, `V` the allocated node count including the root, and `H` the longest stored key length. Both implementations take O(L) time for normal insertion/search/prefix queries with alphabet size 26. The adaptation adds a validation pass and keeps the same asymptotic bound; it is **not a demonstrated speedup**. Both allocate exactly `k` nodes for a successful missing suffix and no new nodes for an existing path.

For the concrete invalid input `ab#c` on an empty trie, the baseline inserts the different word `abc` and allocates three nodes. The adaptation returns false, allocates zero nodes and leaves that word and its prefixes absent. For allocation failures, the harness fails each of four missing-suffix allocation positions after an existing `car` branch and each of six positions in a root-only trie: all **10** failures return false, preserve the prior tree and retain zero extra tracked blocks after rollback. The old failure path is identified by source review; it is not executed as an intentional NULL dereference or assigned a crash-rate statistic.

Both store O(26V) child-pointer slots. The adaptation pays **one additional ownership pointer per node** plus possible struct padding, O(V) extra storage relative to the old layout. Baseline recursive destruction takes O(26V) work and O(H) call-stack space. The ownership chain makes destruction O(V) work and O(1) auxiliary stack; rollback of `k` private nodes likewise takes O(k) work/O(1) stack. These are operation/storage bounds, not measured elapsed-time or RSS reductions. No paired timing benchmark was run; measured gains remain Unknown. Retaining all nodes until whole-trie destruction and an extra validation pass are the trade-offs; deletion, Unicode and concurrent access are outside this example.

## Run and check

From the repository root:

```sh
make test
```

Or run this file alone:

```sh
clang -std=c11 -Wall -Wextra -Werror -pedantic -fsanitize=undefined \
  04_trees_and_graphs/0208_implement_trie/solution.c -o /tmp/trie-practice
/tmp/trie-practice
```

The standalone harness covers seven groups: normal/shared paths; invalid/NULL/high bytes without mutation; constructor and every missing-suffix failure position; allocation-free duplicate/prefix insertion; empty strings; 9,000 deterministic operations against a finite-word oracle plus a final 243-word check; and a 20,000-character key with iterative teardown. Its expected success line is:

```text
[PASSED] Trie: 7 groups, 9000 oracle operations, 10 failed suffix positions, zero tracked blocks retained.
```

Assertions and allocator counts establish those exercised cases, not a universal correctness or memory-safety proof. Local UBSan and full-repository checks are recorded separately from exact-revision hosted CI. No local ASan result or new platform acceptance is implied by the example.
