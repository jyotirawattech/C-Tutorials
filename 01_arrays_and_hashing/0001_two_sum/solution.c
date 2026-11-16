/*
 * Checked Two Sum practice, C11. AI-assisted adaptation, 2026-11-16.
 * Exact platform acceptance for this API/implementation: Not captured.
 * Search earlier indices; write caller output only after finding a pair.
 */
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef TWO_SUM_NO_TEST_MAIN
static void *test_allocate(size_t bytes);
static void test_release(void *pointer);
#define TWO_SUM_MALLOC test_allocate
#define TWO_SUM_FREE test_release
#else
#if defined(TWO_SUM_MALLOC) != defined(TWO_SUM_FREE)
#error "Supply both TWO_SUM_MALLOC and TWO_SUM_FREE, or neither"
#endif
#ifndef TWO_SUM_MALLOC
#define TWO_SUM_MALLOC malloc
#define TWO_SUM_FREE free
#endif
#endif

typedef enum {
    TWO_SUM_FOUND, TWO_SUM_NO_PAIR, TWO_SUM_INVALID, TWO_SUM_ALLOCATION_FAILURE
} TwoSumStatus;
typedef struct HashNode {
    int key;
    size_t index;
    struct HashNode *next;
} HashNode;
typedef struct {
    size_t capacity;
    HashNode **buckets;
} HashMap;

static size_t hash_key(int key, size_t capacity) {
    return (size_t)((unsigned int)key * 2654435761u) % capacity;
}
static HashMap *hashmap_create(size_t capacity) {
    HashMap *map = TWO_SUM_MALLOC(sizeof *map);
    if (!map) return NULL;
    map->capacity = capacity;
    map->buckets = TWO_SUM_MALLOC(capacity * sizeof *map->buckets);
    if (!map->buckets) { TWO_SUM_FREE(map); return NULL; }
    for (size_t i = 0; i < capacity; ++i) map->buckets[i] = NULL;
    return map;
}
static bool hashmap_insert(HashMap *map, int key, size_t index) {
    HashNode *node = TWO_SUM_MALLOC(sizeof *node);
    if (!node) return false;
    size_t bucket = hash_key(key, map->capacity);
    node->key = key;
    node->index = index;
    node->next = map->buckets[bucket];
    map->buckets[bucket] = node;
    return true;
}
static bool hashmap_find(const HashMap *map, int key, size_t *index) {
    for (HashNode *node = map->buckets[hash_key(key, map->capacity)];
         node; node = node->next) {
        if (node->key == key) { *index = node->index; return true; }
    }
    return false;
}
static void hashmap_free(HashMap *map) {
    for (size_t i = 0; i < map->capacity; ++i) {
        HashNode *node = map->buckets[i];
        while (node) {
            HashNode *next = node->next;
            TWO_SUM_FREE(node);
            node = next;
        }
    }
    TWO_SUM_FREE(map->buckets);
    TWO_SUM_FREE(map);
}
/* Each guard addition is representable for the selected sign branch. */
static bool checked_complement(int target, int value, int *complement) {
    if ((value > 0 && target < INT_MIN + value) ||
        (value < 0 && target > INT_MAX + value)) return false;
    *complement = target - value;
    return true;
}
/*
 * For representable lengths, nums names count readable ints (NULL only at 0).
 * pair names two writable caller-owned size_t objects and must not alias nums.
 * Representation-invalid lengths are rejected before allocation/array reads.
 * Matching allocator hooks require ordinary malloc/free ownership semantics.
 */
TwoSumStatus twoSumChecked(const int *nums, size_t count, int target,
                          size_t pair[2]) {
    if (!pair || (!nums && count != 0)) return TWO_SUM_INVALID;
    if (count > SIZE_MAX / sizeof *nums || count > SIZE_MAX / 2)
        return TWO_SUM_INVALID;
    if (count < 2) return TWO_SUM_NO_PAIR;
    size_t capacity = count < 8 ? 16 : count * 2;
    if (capacity > SIZE_MAX / sizeof(HashNode *)) return TWO_SUM_INVALID;
    HashMap *map = hashmap_create(capacity);
    if (!map) return TWO_SUM_ALLOCATION_FAILURE;
    for (size_t i = 0; i < count; ++i) {
        int complement;
        size_t earlier;
        if (checked_complement(target, nums[i], &complement) &&
            hashmap_find(map, complement, &earlier)) {
            hashmap_free(map);
            pair[0] = earlier;
            pair[1] = i;
            return TWO_SUM_FOUND;
        }
        /* Retain baseline insertion work, including the final element. */
        if (!hashmap_insert(map, nums[i], i)) {
            hashmap_free(map);
            return TWO_SUM_ALLOCATION_FAILURE;
        }
    }
    hashmap_free(map);
    return TWO_SUM_NO_PAIR;
}

#ifndef TWO_SUM_NO_TEST_MAIN
/* Only the standalone oracle depends on wider test arithmetic. */
_Static_assert(INT_MAX <= INT64_MAX / 2 && INT_MIN >= INT64_MIN / 2,
               "Standalone oracle requires int sums to fit int64_t");
static size_t test_live_blocks, test_peak_blocks, test_attempts;
static size_t test_fail_after = SIZE_MAX, test_oracle_cases;
static void *test_allocate(size_t bytes) {
    ++test_attempts;
    if (test_fail_after == 0) return NULL;
    if (test_fail_after != SIZE_MAX) --test_fail_after;
    void *result = malloc(bytes);
    if (result) {
        ++test_live_blocks;
        if (test_live_blocks > test_peak_blocks) test_peak_blocks = test_live_blocks;
    }
    return result;
}
static void test_release(void *pointer) {
    if (!pointer) return;
    assert(test_live_blocks > 0);
    --test_live_blocks;
    free(pointer);
}
static void reset_allocator(void) {
    assert(test_live_blocks == 0);
    test_live_blocks = test_peak_blocks = test_attempts = 0;
    test_fail_after = SIZE_MAX;
}
static bool oracle_exists(const int *nums, size_t count, int target) {
    for (size_t i = 0; i < count; ++i)
        for (size_t j = i + 1; j < count; ++j)
            if ((int64_t)nums[i] + (int64_t)nums[j] == (int64_t)target) return true;
    return false;
}
static void check_case(const int *nums, size_t count, int target) {
    reset_allocator();
    size_t pair[2] = {SIZE_MAX, SIZE_MAX - 1};
    bool expected = oracle_exists(nums, count, target);
    TwoSumStatus status = twoSumChecked(nums, count, target, pair);
    assert(status == (expected ? TWO_SUM_FOUND : TWO_SUM_NO_PAIR));
    if (expected) {
        assert(pair[0] < pair[1] && pair[1] < count);
        assert((int64_t)nums[pair[0]] + (int64_t)nums[pair[1]] == (int64_t)target);
    } else assert(pair[0] == SIZE_MAX && pair[1] == SIZE_MAX - 1);
    assert(test_live_blocks == 0);
}
static void test_standard(void) {
    const int a[] = {2, 7, 11, 15}, b[] = {3, 2, 4}, c[] = {-3, 4, 3, 90};
    const int duplicate[] = {3, 3}, missing[] = {1, 2, 4};
    check_case(a, 4, 9); check_case(b, 3, 6); check_case(c, 4, 0);
    check_case(duplicate, 2, 6); check_case(missing, 3, 100);
}
static void test_extremes(void) {
    const int low_then_pair[] = {INT_MIN, 0, 1};
    const int high_then_pair[] = {INT_MAX, 0, -2};
    const int extremes[] = {INT_MIN, INT_MAX};
    const int lows[] = {INT_MIN, INT_MIN}, highs[] = {INT_MAX, INT_MAX};
    const int boundary[] = {INT_MIN, INT_MAX, -1, 0, 1, INT_MIN + 1, INT_MAX - 1};
    check_case(low_then_pair, 3, 1); check_case(high_then_pair, 3, -2);
    check_case(extremes, 2, -1); check_case(lows, 2, 0); check_case(highs, 2, -2);
    check_case(boundary, 7, INT_MIN); check_case(boundary, 7, INT_MAX);
}
static void test_invalid_and_short(void) {
    reset_allocator();
    const int one = 7;
    size_t pair[2] = {42, 43};
    assert(twoSumChecked(NULL, 0, 0, pair) == TWO_SUM_NO_PAIR);
    assert(twoSumChecked(&one, 1, 7, pair) == TWO_SUM_NO_PAIR);
    assert(twoSumChecked(NULL, 1, 0, pair) == TWO_SUM_INVALID);
    assert(twoSumChecked(&one, 1, 0, NULL) == TWO_SUM_INVALID);
    assert(twoSumChecked(&one, SIZE_MAX, 0, pair) == TWO_SUM_INVALID);
    assert(twoSumChecked(&one, SIZE_MAX / sizeof(int) + 1, 0, pair) == TWO_SUM_INVALID);
    assert(twoSumChecked(&one, SIZE_MAX / 2 + 1, 0, pair) == TWO_SUM_INVALID);
    assert(twoSumChecked(&one, SIZE_MAX / (2 * sizeof(HashNode *)) + 1,
                         0, pair) == TWO_SUM_INVALID);
    assert(test_attempts == 0 && test_live_blocks == 0);
    assert(pair[0] == 42 && pair[1] == 43);
}
static void test_collisions(void) {
    const int nums[] = {0, 16, 32, 48, 64, 80, 96, 112};
    for (size_t i = 0; i < 8; ++i) assert(hash_key(nums[i], 16) == 0);
    check_case(nums, 8, 1024); check_case(nums, 8, 208);
}
static void fail_every_allocation(const int *nums, size_t count, int target,
                                  size_t successful_attempts) {
    assert(count <= 5);
    int before[5] = {0};
    for (size_t i = 0; i < count; ++i) before[i] = nums[i];
    for (size_t fail = 0; fail < successful_attempts; ++fail) {
        reset_allocator(); test_fail_after = fail;
        size_t pair[2] = {123, 456};
        assert(twoSumChecked(nums, count, target, pair) == TWO_SUM_ALLOCATION_FAILURE);
        assert(pair[0] == 123 && pair[1] == 456);
        assert(test_live_blocks == 0 && test_attempts == fail + 1);
        for (size_t i = 0; i < count; ++i) assert(nums[i] == before[i]);
    }
    reset_allocator();
    size_t pair[2] = {123, 456};
    (void)twoSumChecked(nums, count, target, pair);
    assert(test_attempts == successful_attempts && test_live_blocks == 0);
}
static void test_failures(void) {
    const int absent[] = {1, 3, 5, 7, 9}, found[] = {1, 4, 7, 9};
    fail_every_allocation(absent, 5, 100, 7);
    fail_every_allocation(found, 4, 13, 5);
}
static void test_allocation_work(void) {
    reset_allocator();
    const int nums[] = {1, 3, 5, 7};
    size_t pair[2] = {SIZE_MAX, SIZE_MAX};
    assert(twoSumChecked(nums, 4, 100, pair) == TWO_SUM_NO_PAIR);
    assert(test_attempts == 6 && test_peak_blocks == 6 && test_live_blocks == 0);
    assert(pair[0] == SIZE_MAX && pair[1] == SIZE_MAX);
}
static void test_exhaustive_oracle(void) {
    size_t possibilities = 1;
    for (size_t length = 0; length <= 5; ++length) {
        for (size_t code = 0; code < possibilities; ++code) {
            int nums[5] = {0}; size_t value = code;
            for (size_t i = 0; i < length; ++i) {
                nums[i] = (int)(value % 3) - 1; value /= 3;
            }
            for (int target = -2; target <= 2; ++target) {
                check_case(nums, length, target); ++test_oracle_cases;
            }
        }
        possibilities *= 3;
    }
}
static void test_random_oracle(void) {
    uint32_t state = 1;
    const int edge[] = {INT_MIN, INT_MAX, -1, 0, 1, INT_MIN + 1, INT_MAX - 1};
    for (size_t trial = 0; trial < 20000; ++trial) {
        state = state * UINT32_C(1664525) + UINT32_C(1013904223);
        size_t length = (state >> 8) % 11;
        int nums[10] = {0}, before[10] = {0};
        for (size_t i = 0; i < length; ++i) {
            state = state * UINT32_C(1664525) + UINT32_C(1013904223);
            nums[i] = (state & 3u) == 0 ? edge[(state >> 8) % 7]
                                      : (int)((state >> 8) % 31) - 15;
            before[i] = nums[i];
        }
        state = state * UINT32_C(1664525) + UINT32_C(1013904223);
        int target = (state & 3u) == 0 ? edge[(state >> 8) % 7]
                                     : (int)((state >> 8) % 41) - 20;
        check_case(nums, length, target); ++test_oracle_cases;
        for (size_t i = 0; i < length; ++i) assert(nums[i] == before[i]);
    }
}
int main(void) {
    test_standard(); test_extremes(); test_invalid_and_short(); test_collisions();
    test_failures(); test_allocation_work(); test_exhaustive_oracle(); test_random_oracle();
    assert(test_oracle_cases == 21820 && test_live_blocks == 0);
    printf("[OBSERVED] Two Sum: no-pair four-value case uses 6 allocations; HashNode=%zu bytes on this ABI.\n", sizeof(HashNode));
    puts("[PASSED] Two Sum: 8 groups, 21820 oracle cases, 12 allocation failure cases, zero tracked blocks retained.");
    return 0;
}
#endif
