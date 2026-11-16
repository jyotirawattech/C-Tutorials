# Checked Two Sum in C

Practice for [LeetCode 1: Two Sum](https://leetcode.com/problems/two-sum/), improved on 16 November 2026. This AI-assisted adaptation of the existing standalone example is **not a new solve or newly Accepted submission**. The earlier practice example's original authorship, solve date and assistance are **Unknown**. Exact judge acceptance, runtime, memory and Beats for this API/implementation: **Not captured**. The separate historical Accepted source and its dates remain unchanged.

The useful question is whether full-range integer inputs and allocation failures can return a clear result without overflowing arithmetic, partially writing output or retaining allocations. The previous example used unchecked signed `target - nums[i]` and `numsSize * 2`, dereferenced `returnSize` without validating it, and did not check per-node allocation. Its successful-operation cleanup already freed its memory; this change claims no baseline normal-path leak repair.

## Contract and invariant

The practice API intentionally differs from the judge interface:

```c
typedef enum {
    TWO_SUM_FOUND, TWO_SUM_NO_PAIR, TWO_SUM_INVALID,
    TWO_SUM_ALLOCATION_FAILURE
} TwoSumStatus;

TwoSumStatus twoSumChecked(const int *nums, size_t count, int target,
                          size_t pair[2]);
```

For a representable length, `nums` names `count` readable ints; NULL is permitted only at length zero. `pair` names two writable caller-owned `size_t` objects and must not alias the input. Output is written **only** for `TWO_SUM_FOUND`, with `pair[0] < pair[1] < count`; any valid pair may be returned. Empty or single-element inputs return `TWO_SUM_NO_PAIR` without allocation. NULL output, NULL input with a nonzero length and representation-invalid array/table lengths return `TWO_SUM_INVALID` before allocation or input-array reads. C cannot validate that an arbitrary pointer actually names the promised storage.

Keys and targets may use the full int range. Before calculating `target - value`, the code checks the relevant `INT_MIN + value` or `INT_MAX + value` bound. These guard additions are themselves representable for the chosen sign. If the complement cannot be represented as an int, no earlier int can equal it, so that lookup is skipped while scanning continues. This does not rely on a wider integer type in the implementation. For example, `{INT_MIN, 0, 1}` with target 1 still finds the later pair 0 and 1.

At iteration `i`, the separate-chaining map contains only values at indices below `i`. Lookup occurs before insertion, so an index cannot pair with itself, and repeated values can form a pair at distinct positions. Every map, bucket-array and node allocation is checked. A rejected allocation frees all already-owned objects and returns `TWO_SUM_ALLOCATION_FAILURE` with unchanged input/output. The implementation is single-threaded; caller storage, matching allocator ownership and ordinary malloc/free semantics are required. Defining `TWO_SUM_NO_TEST_MAIN` removes the harness; paired `TWO_SUM_MALLOC`/`TWO_SUM_FREE` hooks may then replace malloc/free.

## How much improves, and why?

The fair baseline is the repository's [previous standalone implementation at ddb8f3d](https://github.com/jyotirawattech/C-Tutorials/blob/ddb8f3df94a44cfd443df663622b34cf02281a95/01_arrays_and_hashing/0001_two_sum/solution.c). Both versions use the same search-before-insert, separate-chaining method. Defensive full-int/error handling and explicit status results are additional requirements here; the comparison does not imply the constrained judge interface required them.

Let `n` be input length and `B = max(16, 2n)` the bucket count for inputs needing a map. Both versions have expected O(n) total work under a suitable hash/key distribution, including Θ(B) initialization and Θ(B + k) teardown after storing `k <= n` nodes. Adversarial chains can make lookup work O(n²); the fixed hash is not a universal linear-time guarantee. Both have O(n) auxiliary storage. The normal algorithm has **no established asymptotic speedup** from this change.

The caller-owned output removes exactly **one dynamic allocation**: the old two-int result array. Retaining the baseline's insertion work makes the count straightforward. A successful no-pair run with `n >= 2` uses `n + 3` allocation calls in the baseline and `n + 2` here. A pair found at zero-based iteration `i` uses `i + 3` versus `i + 2`. On the same safe `{1, 3, 5, 7}`, target 100 case, the baseline observation records **7** allocation calls and the new harness records **6**, both with zero retained tracked blocks. These are allocation-work counts, not elapsed-time gains or memory/RSS reductions.

Output now occupies two caller-owned `size_t` values, and storing `size_t` indices can make each hash node larger than the old int-index node. On the local 16 November 2026 build, the compiled baseline/new node-size observations were **16 versus 24 bytes**; local C ABI type widths give **8 bytes** for the old two-int result payload versus **16 bytes** for the new two-size_t caller output. These are ABI-specific object-size observations, not allocator overhead, peak process memory or RSS. Therefore fewer allocation calls do **not** establish lower total storage. The named baseline's unchecked overflow/failure risks are source-review findings; no intentional old NULL dereference or signed-overflow execution is used as evidence.

The harness injects every allocation failure position on two chosen paths: seven positions on a five-element no-pair path and five on a four-element found-pair path, **12 injected failure cases** in total. Each returns the allocation-failure status, preserves input/output and retains zero tracked blocks. These bounded cases are not a proof of every execution. No paired elapsed-time benchmark was run; measured speedup and memory/RSS reduction remain **Unknown**.

## Run and check

From the repository root:

```sh
make test
```

Or run this harness alone:

```sh
clang -std=c11 -Wall -Wextra -Werror -pedantic -fsanitize=undefined \
  01_arrays_and_hashing/0001_two_sum/solution.c -o /tmp/two-sum-practice
/tmp/two-sum-practice
```

Eight groups cover ordinary/duplicate/no-pair results, signed extremes with later valid pairs, NULL/short/invalid lengths, deliberate collisions, all 12 selected allocation-failure cases, the six-allocation observation, 1,820 exhaustive small-alphabet oracle cases and 20,000 seeded mixed/extreme oracle cases. The standalone oracle uses wider test arithmetic and a compile-time assertion that sums of two ints fit in `int64_t` on the tested ABI; the implementation's complement guard has no such dependency. Huge-length tests reject unrepresentable lengths before any huge allocation or array read.

Expected final success line:

```text
[PASSED] Two Sum: 8 groups, 21820 oracle cases, 12 allocation failure cases, zero tracked blocks retained.
```

Assertions and allocation counts describe exercised cases, not universal correctness or memory safety. Local fail-fast UBSan, full-repository checks and exact-revision hosted CI retain separate evidence. No local ASan result or new platform verdict is implied.
