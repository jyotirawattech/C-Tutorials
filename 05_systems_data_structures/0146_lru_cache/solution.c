/*
 * Checked LRU practice, C11. AI-assisted adaptation, 2026-11-15.
 * New-key node and hash entry are staged before any eviction or list mutation.
 * Platform acceptance for this API/implementation: Not captured.
 */
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef LRU_NO_TEST_MAIN
static void *test_allocate(size_t bytes);
static void test_release(void *pointer);
#define LRU_MALLOC test_allocate
#define LRU_FREE test_release
#else
#ifndef LRU_MALLOC
#define LRU_MALLOC malloc
#endif
#ifndef LRU_FREE
#define LRU_FREE free
#endif
#endif

typedef struct DListNode {
    int key, value;
    struct DListNode *prev, *next;
} DListNode;

typedef struct HashEntry {
    int key;
    DListNode *node;
    struct HashEntry *next;
} HashEntry;

typedef struct {
    int capacity, size, hash_capacity;
    HashEntry **table;
    DListNode *head, *tail;
} LRUCache;

static unsigned int lru_hash(int key, int capacity) {
    return ((unsigned int)key * 2654435761u) % (unsigned int)capacity;
}

static void dlist_add_to_head(LRUCache *cache, DListNode *node) {
    node->next = cache->head->next;
    node->prev = cache->head;
    cache->head->next->prev = node;
    cache->head->next = node;
}

static void dlist_remove_node(DListNode *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

static void dlist_move_to_head(LRUCache *cache, DListNode *node) {
    dlist_remove_node(node);
    dlist_add_to_head(cache, node);
}

static DListNode *hash_find(const LRUCache *cache, int key) {
    unsigned int bucket = lru_hash(key, cache->hash_capacity);
    for (HashEntry *entry = cache->table[bucket]; entry; entry = entry->next)
        if (entry->key == key) return entry->node;
    return NULL;
}

static void hash_remove(LRUCache *cache, int key) {
    unsigned int bucket = lru_hash(key, cache->hash_capacity);
    HashEntry **link = &cache->table[bucket];
    while (*link && (*link)->key != key) link = &(*link)->next;
    assert(*link); /* Every list node has exactly one corresponding entry. */
    HashEntry *removed = *link;
    *link = removed->next;
    LRU_FREE(removed);
}

LRUCache *lruCacheCreate(int capacity) {
    /* Keep integer fields representable, before either multiplication. */
    if (capacity <= 0 || capacity > INT_MAX / 2) return NULL;
    int buckets = capacity < 8 ? 16 : capacity * 2;
    if ((uintmax_t)buckets > (uintmax_t)(SIZE_MAX / sizeof(HashEntry *))) return NULL;

    LRUCache *cache = LRU_MALLOC(sizeof *cache);
    if (!cache) return NULL;
    cache->capacity = capacity;
    cache->size = 0;
    cache->hash_capacity = buckets;
    cache->head = NULL;
    cache->tail = NULL;
    cache->table = LRU_MALLOC((size_t)buckets * sizeof *cache->table);
    if (!cache->table) { LRU_FREE(cache); return NULL; }
    for (int i = 0; i < buckets; ++i) cache->table[i] = NULL;
    cache->head = LRU_MALLOC(sizeof *cache->head);
    if (!cache->head) { LRU_FREE(cache->table); LRU_FREE(cache); return NULL; }
    cache->tail = LRU_MALLOC(sizeof *cache->tail);
    if (!cache->tail) {
        LRU_FREE(cache->head); LRU_FREE(cache->table); LRU_FREE(cache);
        return NULL;
    }
    cache->head->key = cache->head->value = 0;
    cache->tail->key = cache->tail->value = 0;
    cache->head->prev = NULL;
    cache->head->next = cache->tail;
    cache->tail->prev = cache->head;
    cache->tail->next = NULL;
    return cache;
}

/* out must be writable caller-owned storage, not part of the cache. */
bool lruCacheGet(LRUCache *cache, int key, int *out) {
    if (!cache || !out) return false;
    DListNode *node = hash_find(cache, key);
    if (!node) return false;
    dlist_move_to_head(cache, node);
    *out = node->value;
    return true;
}

bool lruCachePut(LRUCache *cache, int key, int value) {
    if (!cache) return false;
    DListNode *existing = hash_find(cache, key);
    if (existing) {
        existing->value = value;
        dlist_move_to_head(cache, existing);
        return true;
    }

    DListNode *node = LRU_MALLOC(sizeof *node);
    if (!node) return false;
    HashEntry *entry = LRU_MALLOC(sizeof *entry);
    if (!entry) { LRU_FREE(node); return false; }
    node->key = key;
    node->value = value;
    entry->key = key;
    entry->node = node;

    /* No fallible allocation remains: now eviction and commit can begin. */
    if (cache->size == cache->capacity) {
        DListNode *victim = cache->tail->prev;
        dlist_remove_node(victim);
        hash_remove(cache, victim->key);
        LRU_FREE(victim);
        --cache->size;
    }
    unsigned int bucket = lru_hash(key, cache->hash_capacity);
    entry->next = cache->table[bucket];
    cache->table[bucket] = entry;
    dlist_add_to_head(cache, node);
    ++cache->size;
    return true;
}

void lruCacheFree(LRUCache *cache) {
    if (!cache) return;
    for (int i = 0; i < cache->hash_capacity; ++i) {
        HashEntry *entry = cache->table[i];
        while (entry) {
            HashEntry *next = entry->next;
            LRU_FREE(entry);
            entry = next;
        }
    }
    DListNode *node = cache->head;
    while (node) {
        DListNode *next = node->next;
        LRU_FREE(node);
        node = next;
    }
    LRU_FREE(cache->table);
    LRU_FREE(cache);
}

#ifndef LRU_NO_TEST_MAIN
static size_t test_live_blocks, test_peak_live, test_attempts;
static size_t test_fail_after = SIZE_MAX;
static const LRUCache *test_watch_cache;
static int test_first_allocation_size = -1;

static void *test_allocate(size_t bytes) {
    ++test_attempts;
    if (test_watch_cache && test_first_allocation_size == -1)
        test_first_allocation_size = test_watch_cache->size;
    if (test_fail_after == 0) return NULL;
    if (test_fail_after != SIZE_MAX) --test_fail_after;
    void *result = malloc(bytes);
    if (result) {
        ++test_live_blocks;
        if (test_live_blocks > test_peak_live) test_peak_live = test_live_blocks;
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
    test_fail_after = SIZE_MAX;
    test_peak_live = test_attempts = 0;
    test_watch_cache = NULL;
    test_first_allocation_size = -1;
}

static void check_structure(const LRUCache *cache) {
    assert(cache && cache->head && cache->tail);
    assert(cache->head->prev == NULL && cache->tail->next == NULL);
    assert(cache->size >= 0 && cache->size <= cache->capacity);
    int nodes = 0, entries = 0;
    const DListNode *previous = cache->head;
    for (DListNode *node = cache->head->next; node != cache->tail; node = node->next) {
        assert(node && node->prev == previous);
        assert(hash_find(cache, node->key) == node);
        previous = node;
        assert(++nodes <= cache->size);
    }
    assert(cache->tail->prev == previous && previous->next == cache->tail);
    for (int i = 0; i < cache->hash_capacity; ++i) {
        for (HashEntry *entry = cache->table[i]; entry; entry = entry->next) {
            assert(entry->node && entry->key == entry->node->key);
            assert(lru_hash(entry->key, cache->hash_capacity) == (unsigned int)i);
            assert(hash_find(cache, entry->key) == entry->node);
            assert(++entries <= cache->size);
        }
    }
    assert(nodes == cache->size && entries == cache->size);
}

static uintptr_t snapshot(const LRUCache *cache) {
    uintptr_t hash = (uintptr_t)cache->size;
    for (DListNode *node = cache->head; node; node = node->next) {
        hash = hash * 31u + (uintptr_t)node;
        hash = hash * 31u + (uintptr_t)node->prev;
        hash = hash * 31u + (uintptr_t)node->next;
        hash = hash * 31u + (unsigned int)node->key;
        hash = hash * 31u + (unsigned int)node->value;
    }
    for (int i = 0; i < cache->hash_capacity; ++i) {
        hash = hash * 31u + (uintptr_t)cache->table[i];
        for (HashEntry *entry = cache->table[i]; entry; entry = entry->next) {
            hash = hash * 31u + (uintptr_t)entry;
            hash = hash * 31u + (uintptr_t)entry->node;
            hash = hash * 31u + (uintptr_t)entry->next;
            hash = hash * 31u + (unsigned int)entry->key;
        }
    }
    return hash;
}

static void test_standard(void) {
    reset_allocator();
    LRUCache *cache = lruCacheCreate(2); assert(cache);
    int out = 77;
    assert(lruCachePut(cache, 1, 1) && lruCachePut(cache, 2, 2));
    assert(lruCacheGet(cache, 1, &out) && out == 1);
    assert(lruCachePut(cache, 3, 3));
    assert(!lruCacheGet(cache, 2, &out) && out == 1);
    assert(lruCachePut(cache, 4, 4));
    assert(!lruCacheGet(cache, 1, &out));
    assert(lruCacheGet(cache, 3, &out) && out == 3);
    assert(lruCacheGet(cache, 4, &out) && out == 4);
    check_structure(cache);
    lruCacheFree(cache); assert(test_live_blocks == 0);
}

static void test_constructor(void) {
    reset_allocator();
    assert(!lruCacheCreate(0) && !lruCacheCreate(-1));
    assert(!lruCacheCreate(INT_MAX) && !lruCacheCreate(INT_MAX / 2 + 1));
    assert(test_attempts == 0);
    for (size_t failure = 0; failure <= 4; ++failure) {
        reset_allocator(); test_fail_after = failure;
        LRUCache *cache = lruCacheCreate(3);
        assert((cache != NULL) == (failure == 4));
        if (cache) { assert(test_live_blocks == 4); check_structure(cache); }
        test_fail_after = SIZE_MAX;
        lruCacheFree(cache); assert(test_live_blocks == 0);
    }
    reset_allocator(); test_fail_after = 0;
    assert(!lruCacheCreate(INT_MAX / 2));
    assert(test_live_blocks == 0 && test_attempts <= 1); /* No huge allocation. */
    test_fail_after = SIZE_MAX;
}

static void test_integer_values(void) {
    reset_allocator();
    LRUCache *cache = lruCacheCreate(3); assert(cache);
    assert(lruCachePut(cache, INT_MIN, INT_MAX));
    assert(lruCachePut(cache, INT_MAX, INT_MIN));
    assert(lruCachePut(cache, -1, -1));
    int out = 12;
    assert(lruCacheGet(cache, INT_MIN, &out) && out == INT_MAX);
    assert(lruCacheGet(cache, INT_MAX, &out) && out == INT_MIN);
    assert(lruCacheGet(cache, -1, &out) && out == -1);
    uintptr_t before = snapshot(cache);
    assert(!lruCacheGet(cache, 0, &out) && out == -1);
    assert(!lruCacheGet(cache, INT_MIN, NULL));
    assert(snapshot(cache) == before);
    assert(!lruCachePut(NULL, 1, 1) && !lruCacheGet(NULL, 1, &out));
    assert(out == -1); check_structure(cache);
    lruCacheFree(cache); lruCacheFree(NULL); assert(test_live_blocks == 0);
}

static void test_no_allocation(void) {
    reset_allocator();
    LRUCache *cache = lruCacheCreate(2); assert(cache);
    assert(lruCachePut(cache, 1, 10) && lruCachePut(cache, 2, 20));
    size_t calls = test_attempts;
    test_fail_after = 0;
    assert(lruCachePut(cache, 1, -1));
    int out = 0; assert(lruCacheGet(cache, 2, &out) && out == 20);
    assert(test_attempts == calls && cache->head->next->key == 2);
    test_fail_after = SIZE_MAX;
    assert(lruCachePut(cache, 3, 30));
    assert(!lruCacheGet(cache, 1, &out));
    check_structure(cache); lruCacheFree(cache); assert(test_live_blocks == 0);
}

static void test_put_failures(void) {
    /* Four positions: node/entry failure in a full and non-full cache. */
    for (int full = 0; full <= 1; ++full) {
        for (size_t failure = 0; failure < 2; ++failure) {
            reset_allocator();
            LRUCache *cache = lruCacheCreate(2); assert(cache);
            assert(lruCachePut(cache, 1, 10));
            if (full) assert(lruCachePut(cache, 2, 20));
            uintptr_t before = snapshot(cache);
            size_t blocks = test_live_blocks;
            test_fail_after = failure;
            assert(!lruCachePut(cache, 3, 30));
            assert(test_live_blocks == blocks && snapshot(cache) == before);
            assert(hash_find(cache, 1)->value == 10 && !hash_find(cache, 3));
            if (full) assert(hash_find(cache, 2)->value == 20);
            check_structure(cache);
            test_fail_after = SIZE_MAX;
            assert(lruCachePut(cache, 3, 30));
            if (full) assert(!hash_find(cache, 1) && hash_find(cache, 2));
            else assert(hash_find(cache, 1));
            check_structure(cache); lruCacheFree(cache); assert(test_live_blocks == 0);
        }
    }
}

static void test_single_and_collisions(void) {
    reset_allocator();
    LRUCache *single = lruCacheCreate(1); assert(single);
    assert(lruCachePut(single, 1, 11));
    for (size_t failure = 0; failure < 2; ++failure) {
        uintptr_t before = snapshot(single); test_fail_after = failure;
        assert(!lruCachePut(single, 2, 22) && snapshot(single) == before);
        assert(test_live_blocks == 6); test_fail_after = SIZE_MAX;
    }
    assert(lruCachePut(single, 2, 22));
    assert(!hash_find(single, 1) && hash_find(single, 2));
    check_structure(single); lruCacheFree(single); assert(test_live_blocks == 0);
    LRUCache *cache = lruCacheCreate(3); assert(cache);
    assert(lru_hash(0, 16) == lru_hash(16, 16));
    assert(lru_hash(16, 16) == lru_hash(32, 16));
    assert(lruCachePut(cache, 0, 0) && lruCachePut(cache, 16, 1));
    assert(lruCachePut(cache, 32, 2));
    int out = -1;
    assert(lruCacheGet(cache, 0, &out) && out == 0);
    assert(lruCachePut(cache, 48, 3));
    assert(!hash_find(cache, 16) && hash_find(cache, 32) && hash_find(cache, 0));
    check_structure(cache); lruCacheFree(cache); assert(test_live_blocks == 0);
}

static void test_staging_observation(void) {
    reset_allocator();
    LRUCache *cache = lruCacheCreate(2); assert(cache);
    assert(lruCachePut(cache, 1, 1) && lruCachePut(cache, 2, 2));
    size_t steady = test_live_blocks;
    test_peak_live = steady;
    test_watch_cache = cache;
    assert(lruCachePut(cache, 3, 3));
    test_watch_cache = NULL;
    assert(test_first_allocation_size == 2);
    assert(steady == 8 && test_peak_live == steady + 2 && test_live_blocks == steady);
    check_structure(cache); lruCacheFree(cache); assert(test_live_blocks == 0);
}

typedef struct { int keys[5], values[5], size; } Oracle;

static int oracle_index(const Oracle *model, int key) {
    for (int i = 0; i < model->size; ++i) if (model->keys[i] == key) return i;
    return -1;
}

static void oracle_touch(Oracle *model, int index, int key, int value) {
    if (index < 0) { if (model->size < 5) ++model->size; index = model->size - 1; }
    for (int i = index; i > 0; --i) {
        model->keys[i] = model->keys[i - 1]; model->values[i] = model->values[i - 1];
    }
    model->keys[0] = key; model->values[0] = value;
}

static void test_oracle(void) {
    reset_allocator();
    LRUCache *cache = lruCacheCreate(5); assert(cache);
    Oracle model = {{0}, {0}, 0};
    uint32_t state = 146;
    for (size_t operation = 0; operation < 12000; ++operation) {
        state = state * UINT32_C(1664525) + UINT32_C(1013904223);
        int key = (int)((state >> 8) % 21) - 10;
        int index = oracle_index(&model, key);
        if (state & 1u) {
            int value = (state & 2u) ? INT_MIN : (state & 4u) ? INT_MAX : -1;
            assert(lruCachePut(cache, key, value));
            oracle_touch(&model, index, key, value);
        } else {
            int out = 42;
            assert(lruCacheGet(cache, key, &out) == (index >= 0));
            if (index >= 0) {
                assert(out == model.values[index]);
                oracle_touch(&model, index, key, out);
            } else assert(out == 42);
        }
        check_structure(cache);
        assert(cache->size == model.size);
        DListNode *node = cache->head->next;
        for (int i = 0; i < model.size; ++i) {
            assert(node->key == model.keys[i] && node->value == model.values[i]);
            node = node->next;
        }
        assert(node == cache->tail && test_live_blocks == (size_t)(4 + 2 * model.size));
    }
    lruCacheFree(cache); assert(test_live_blocks == 0);
}

int main(void) {
    test_standard(); test_constructor(); test_integer_values(); test_no_allocation();
    test_put_failures(); test_single_and_collisions(); test_staging_observation(); test_oracle();
    puts("[PASSED] LRU: 8 groups, 12000 oracle operations, 4 constructor failure positions, 6 put failure cases, zero tracked blocks retained.");
    return 0;
}
#endif
