/*
 * LFU: checked lifetime/failure-path practice, November 2026.
 * AI-assisted adaptation of historical C submission 2029340112; not submitted.
 * The original Accepted source/date remains in leetcode/accepted/0460_*.
 * Retains direct key/frequency tables and per-frequency LRU lists, including
 * empty lists. Fixed domains, single-threaded, live-object caller contract.
 * Define LFU_NO_TEST_MAIN for the core only. LFU_MALLOC/CALLOC/FREE may be
 * overridden together before inclusion for an independent allocator probe.
 */
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

enum { LFU_KEY_SLOTS = 100005, LFU_FREQ_SLOTS = 200005 };

#ifndef LFU_NO_TEST_MAIN
static void *tracked_malloc(size_t size);
static void *tracked_calloc(size_t count, size_t size);
static void tracked_free(void *ptr);
#ifndef LFU_MALLOC
#define LFU_MALLOC tracked_malloc
#endif
#ifndef LFU_CALLOC
#define LFU_CALLOC tracked_calloc
#endif
#ifndef LFU_FREE
#define LFU_FREE tracked_free
#endif
#else
#ifndef LFU_MALLOC
#define LFU_MALLOC malloc
#endif
#ifndef LFU_CALLOC
#define LFU_CALLOC calloc
#endif
#ifndef LFU_FREE
#define LFU_FREE free
#endif
#endif

typedef struct LFUNode {
    int key, val, freq;
    struct LFUNode *prev, *next;
} LFUNode;

typedef struct {
    LFUNode *head, *tail;
    int size;
} LFUList;

typedef struct {
    int capacity, size, min_freq;
    LFUNode *key_to_node[LFU_KEY_SLOTS]; /* owns live data nodes */
    LFUList *freq_to_list[LFU_FREQ_SLOTS]; /* owns lists and their sentinels */
} LFUCache;

static bool valid_key(int key) { return key >= 0 && key < LFU_KEY_SLOTS; }

/* Used for detached/partial lists, or after data nodes were freed separately. */
static void free_list_storage(LFUList *list) {
    if (list == NULL) return;
    LFU_FREE(list->head);
    LFU_FREE(list->tail);
    LFU_FREE(list);
}

static LFUList *make_list(void) {
    LFUList *list = LFU_MALLOC(sizeof(*list));
    if (list == NULL) return NULL;
    *list = (LFUList){NULL, NULL, 0};
    list->head = LFU_CALLOC(1, sizeof(*list->head));
    if (list->head == NULL) goto fail;
    list->tail = LFU_CALLOC(1, sizeof(*list->tail));
    if (list->tail == NULL) goto fail;
    list->head->next = list->tail;
    list->tail->prev = list->head;
    return list;
fail:
    free_list_storage(list);
    return NULL;
}

static void remove_node(LFUList *list, LFUNode *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    list->size--;
}

static void add_front(LFUList *list, LFUNode *node) {
    node->prev = list->head;
    node->next = list->head->next;
    list->head->next->prev = node;
    list->head->next = node;
    list->size++;
}

LFUCache *lfuCreate(int capacity) {
    if (capacity < 0 || capacity > LFU_KEY_SLOTS) return NULL;
    LFUCache *cache = LFU_CALLOC(1, sizeof(*cache));
    if (cache != NULL) cache->capacity = capacity;
    return cache;
}

/* No visible mutation until any destination-list allocation is complete. */
static bool promote(LFUCache *cache, LFUNode *node) {
    int old_freq = node->freq;
    if (old_freq >= LFU_FREQ_SLOTS - 1) return false;
    int next_freq = old_freq + 1;
    LFUList *target = cache->freq_to_list[next_freq];
    if (target == NULL) {
        target = make_list();
        if (target == NULL) return false;
        cache->freq_to_list[next_freq] = target;
    }
    LFUList *old_list = cache->freq_to_list[old_freq];
    remove_node(old_list, node);
    node->freq = next_freq;
    add_front(target, node);
    if (cache->min_freq == old_freq && old_list->size == 0) {
        cache->min_freq = next_freq;
    }
    return true;
}

/* false: invalid/missing key, invalid output, capacity zero, saturation or OOM.
 * A false result never writes *value_out or changes visible cache state.
 */
bool lfuTryGet(LFUCache *cache, int key, int *value_out) {
    if (cache == NULL || value_out == NULL || !valid_key(key) || cache->capacity == 0) return false;
    LFUNode *node = cache->key_to_node[key];
    if (node == NULL || !promote(cache, node)) return false;
    *value_out = node->val;
    return true;
}

bool lfuTryPut(LFUCache *cache, int key, int value) {
    if (cache == NULL || !valid_key(key) || cache->capacity == 0) return false;
    LFUNode *node = cache->key_to_node[key];
    if (node != NULL) {
        if (!promote(cache, node)) return false;
        node->val = value;
        return true;
    }
    /* Prepare both data node and any initial list before selecting an eviction. */
    node = LFU_CALLOC(1, sizeof(*node));
    if (node == NULL) return false;
    LFUList *target = cache->freq_to_list[1];
    LFUList *prepared = NULL;
    if (target == NULL) {
        prepared = make_list();
        if (prepared == NULL) { LFU_FREE(node); return false; }
        target = prepared;
    }
    node->key = key;
    node->val = value;
    node->freq = 1;
    if (prepared != NULL) cache->freq_to_list[1] = prepared;
    if (cache->size == cache->capacity) {
        LFUList *minimum = cache->freq_to_list[cache->min_freq];
        LFUNode *victim = minimum->tail->prev;
        remove_node(minimum, victim);
        cache->key_to_node[victim->key] = NULL;
        LFU_FREE(victim);
        cache->size--;
    }
    cache->key_to_node[key] = node;
    add_front(target, node);
    cache->min_freq = 1;
    cache->size++;
    return true;
}

void lfuFree(LFUCache *cache) {
    if (cache == NULL) return;
    /* Direct key slots own data nodes. List links are aliases, never followed
       after this pass; sentinels and list containers have separate ownership. */
    for (size_t key = 0; key < LFU_KEY_SLOTS; key++) LFU_FREE(cache->key_to_node[key]);
    for (size_t freq = 0; freq < LFU_FREQ_SLOTS; freq++) free_list_storage(cache->freq_to_list[freq]);
    LFU_FREE(cache);
}

#ifndef LFU_NO_TEST_MAIN
/* Bounded synthetic allocator: no host-memory exhaustion is attempted. */
enum { TRACK_SLOTS = 32768 };
typedef struct { void *ptr; size_t bytes; } Allocation;
static Allocation allocations[TRACK_SLOTS];
static size_t allocation_calls, fail_at, live_blocks, live_bytes;

static void *track_allocation(void *ptr, size_t bytes) {
    assert(ptr != NULL); /* real host OOM is separate from injected NULL */
    for (size_t i = 0; i < TRACK_SLOTS; i++) {
        if (allocations[i].ptr == NULL) {
            allocations[i] = (Allocation){ptr, bytes};
            live_blocks++; live_bytes += bytes;
            return ptr;
        }
    }
    assert(!"test allocation capacity exceeded"); abort();
}
static void *tracked_malloc(size_t size) {
    allocation_calls++;
    if (fail_at && allocation_calls == fail_at) return NULL;
    return track_allocation(malloc(size), size);
}
static void *tracked_calloc(size_t count, size_t size) {
    assert(size == 0 || count <= SIZE_MAX / size);
    allocation_calls++;
    if (fail_at && allocation_calls == fail_at) return NULL;
    return track_allocation(calloc(count, size), count * size);
}
static void tracked_free(void *ptr) {
    if (ptr == NULL) return;
    for (size_t i = 0; i < TRACK_SLOTS; i++) {
        if (allocations[i].ptr == ptr) {
            live_blocks--; live_bytes -= allocations[i].bytes;
            allocations[i] = (Allocation){NULL, 0}; free(ptr); return;
        }
    }
    assert(!"untracked or double free"); abort();
}
static void reset_allocator(void) {
    assert(live_blocks == 0 && live_bytes == 0);
    allocation_calls = fail_at = 0;
}
static void fail_nth_next(size_t nth) { fail_at = allocation_calls + nth; }
static void stop_failing(void) { fail_at = 0; }

static void check_structure(const LFUCache *cache) {
    size_t keys = 0, members = 0, lists = 0;
    int minimum = 0;
    assert(cache && cache->capacity >= 0 && cache->capacity <= LFU_KEY_SLOTS);
    assert(cache->freq_to_list[0] == NULL);
    for (size_t key = 0; key < LFU_KEY_SLOTS; key++) {
        const LFUNode *node = cache->key_to_node[key];
        if (node != NULL) {
            assert(node->key == (int)key && node->freq > 0 && node->freq < LFU_FREQ_SLOTS);
            assert(cache->freq_to_list[node->freq] != NULL);
            keys++;
        }
    }
    for (size_t freq = 1; freq < LFU_FREQ_SLOTS; freq++) {
        const LFUList *list = cache->freq_to_list[freq];
        if (list != NULL) {
            assert(list->head && list->tail && list->head->prev == NULL && list->tail->next == NULL);
            const LFUNode *previous = list->head;
            size_t count = 0;
            for (const LFUNode *node = list->head->next; node != list->tail; node = node->next) {
                assert(node && node->prev == previous && node->freq == (int)freq && valid_key(node->key));
                assert(cache->key_to_node[node->key] == node);
                previous = node;
                assert(++count <= (size_t)cache->size);
            }
            assert(list->tail->prev == previous && previous->next == list->tail);
            assert(count == (size_t)list->size);
            if (count && minimum == 0) minimum = (int)freq;
            members += count; lists++;
        }
    }
    assert(keys == members && keys == (size_t)cache->size && cache->size <= cache->capacity);
    assert(cache->min_freq == minimum);
    assert(live_blocks == 1 + keys + 3 * lists);
}

static void test_constructor_and_boundaries(void) {
    reset_allocator();
    assert(lfuCreate(-1) == NULL && lfuCreate(LFU_KEY_SLOTS + 1) == NULL);
    assert(allocation_calls == 0);
    fail_nth_next(1); assert(lfuCreate(2) == NULL);
    assert(live_blocks == 0); stop_failing();
    LFUCache *cache = lfuCreate(0); assert(cache);
    int out = 123;
    assert(!lfuTryGet(cache, 0, &out) && out == 123 && !lfuTryPut(cache, 0, 1));
    assert(!lfuTryGet(NULL, 0, &out) && !lfuTryPut(NULL, 0, 1));
    check_structure(cache); lfuFree(cache); lfuFree(NULL);
    assert(live_blocks == 0 && live_bytes == 0);
    cache = lfuCreate(LFU_KEY_SLOTS); assert(cache);
    assert(lfuTryPut(cache, 0, INT_MIN)); assert(lfuTryPut(cache, LFU_KEY_SLOTS - 1, INT_MAX));
    size_t calls = allocation_calls;
    assert(!lfuTryGet(cache, -1, &out) && !lfuTryGet(cache, LFU_KEY_SLOTS, &out) && out == 123);
    assert(!lfuTryPut(cache, -1, 7) && !lfuTryPut(cache, LFU_KEY_SLOTS, 7));
    assert(!lfuTryGet(cache, 0, NULL) && allocation_calls == calls);
    assert(lfuTryGet(cache, 0, &out) && out == INT_MIN);
    assert(lfuTryGet(cache, LFU_KEY_SLOTS - 1, &out) && out == INT_MAX);
    check_structure(cache); lfuFree(cache); assert(live_blocks == 0 && live_bytes == 0);
}

static void test_canonical_eviction_and_updates(void) {
    reset_allocator(); LFUCache *cache = lfuCreate(2); assert(cache);
    int out = 999;
    assert(lfuTryPut(cache, 1, 1) && lfuTryPut(cache, 2, 2));
    assert(lfuTryGet(cache, 1, &out) && out == 1);
    assert(lfuTryPut(cache, 3, 3));
    out = 999; assert(!lfuTryGet(cache, 2, &out) && out == 999);
    assert(lfuTryGet(cache, 3, &out) && out == 3);
    assert(lfuTryPut(cache, 4, 4)); /* frequency tie evicts least-recent key 1 */
    assert(cache->key_to_node[1] == NULL);
    assert(lfuTryGet(cache, 3, &out) && out == 3);
    assert(lfuTryGet(cache, 4, &out) && out == 4);
    assert(lfuTryPut(cache, 4, 40)); /* existing put counts as a use */
    assert(cache->key_to_node[4]->freq == 3 && cache->key_to_node[4]->val == 40);
    assert(lfuTryPut(cache, 5, -1)); /* tie at frequency 3 evicts key 3 */
    assert(cache->key_to_node[3] == NULL && cache->key_to_node[4] != NULL);
    assert(lfuTryGet(cache, 5, &out) && out == -1); /* negative value is a hit */
    out = -99; assert(!lfuTryGet(cache, 6, &out) && out == -99);
    check_structure(cache); lfuFree(cache); assert(live_blocks == 0 && live_bytes == 0);
}

static void test_new_entry_failures(void) {
    for (size_t failure = 1; failure <= 4; failure++) {
        reset_allocator(); LFUCache *cache = lfuCreate(1); assert(cache);
        fail_nth_next(failure); assert(!lfuTryPut(cache, 1, 11));
        stop_failing();
        assert(cache->key_to_node[1] == NULL && cache->freq_to_list[1] == NULL);
        assert(cache->size == 0 && cache->min_freq == 0 && live_blocks == 1);
        check_structure(cache);
        assert(lfuTryPut(cache, 1, 11)); lfuFree(cache);
        assert(live_blocks == 0 && live_bytes == 0);
    }
    reset_allocator(); LFUCache *cache = lfuCreate(1); assert(cache);
    int out;
    assert(lfuTryPut(cache, 1, 111) && lfuTryGet(cache, 1, &out));
    LFUNode *victim = cache->key_to_node[1];
    LFUNode *old_prev = victim->prev, *old_next = victim->next;
    size_t blocks = live_blocks;
    fail_nth_next(1); assert(!lfuTryPut(cache, 2, 222)); stop_failing();
    assert(cache->key_to_node[1] == victim && cache->key_to_node[2] == NULL);
    assert(victim->val == 111 && victim->freq == 2 && victim->prev == old_prev && victim->next == old_next);
    assert(cache->min_freq == 2 && cache->size == 1 && live_blocks == blocks);
    check_structure(cache);
    assert(lfuTryPut(cache, 2, 222));
    assert(cache->key_to_node[1] == NULL && cache->key_to_node[2]->val == 222);
    check_structure(cache); lfuFree(cache); assert(live_blocks == 0 && live_bytes == 0);
}

static void test_promotion_failures_and_existing_lists(void) {
    for (int operation = 0; operation < 2; operation++) {
        for (size_t failure = 1; failure <= 3; failure++) {
            reset_allocator(); LFUCache *cache = lfuCreate(2); assert(cache);
            assert(lfuTryPut(cache, 1, -1) && lfuTryPut(cache, 2, -2));
            LFUNode *node = cache->key_to_node[1], *previous = node->prev, *next = node->next;
            LFUList *list = cache->freq_to_list[1];
            LFUNode *front = list->head->next, *back = list->tail->prev;
            size_t blocks = live_blocks; int out = 999;
            fail_nth_next(failure);
            bool result = operation == 0 ? lfuTryGet(cache, 1, &out) : lfuTryPut(cache, 1, 99);
            assert(!result && out == 999); stop_failing();
            assert(cache->key_to_node[1] == node && node->val == -1 && node->freq == 1);
            assert(node->prev == previous && node->next == next && list->head->next == front && list->tail->prev == back);
            assert(cache->freq_to_list[2] == NULL && cache->min_freq == 1 && cache->size == 2);
            assert(list->size == 2 && live_blocks == blocks);
            check_structure(cache);
            assert(lfuTryPut(cache, 3, 3)); /* failed access did not rescue key 1 */
            assert(cache->key_to_node[1] == NULL && cache->key_to_node[2] != NULL);
            lfuFree(cache); assert(live_blocks == 0 && live_bytes == 0);
        }
    }
    reset_allocator(); LFUCache *cache = lfuCreate(2); assert(cache); int out;
    assert(lfuTryPut(cache, 1, 1) && lfuTryPut(cache, 2, 2) && lfuTryGet(cache, 1, &out));
    size_t calls = allocation_calls;
    fail_nth_next(1); assert(lfuTryGet(cache, 2, &out) && out == 2);
    assert(allocation_calls == calls); stop_failing();
    assert(lfuTryGet(cache, 1, &out)); /* prepare frequency 3 */
    calls = allocation_calls;
    fail_nth_next(1); assert(lfuTryPut(cache, 2, 22));
    assert(allocation_calls == calls && cache->key_to_node[2]->val == 22); stop_failing();
    assert(cache->freq_to_list[1]->size == 0 && cache->freq_to_list[2]->size == 0);
    check_structure(cache); lfuFree(cache); assert(live_blocks == 0 && live_bytes == 0);
}

static void test_frequency_guard(void) {
    reset_allocator(); LFUCache *cache = lfuCreate(1); assert(cache);
    assert(lfuTryPut(cache, 1, 7));
    LFUList *list = cache->freq_to_list[1];
    cache->freq_to_list[1] = NULL;
    cache->freq_to_list[LFU_FREQ_SLOTS - 1] = list;
    cache->key_to_node[1]->freq = LFU_FREQ_SLOTS - 1;
    cache->min_freq = LFU_FREQ_SLOTS - 1; /* valid synthetic boundary fixture */
    size_t calls = allocation_calls; int out = 314;
    assert(!lfuTryGet(cache, 1, &out) && out == 314);
    assert(!lfuTryPut(cache, 1, 99) && cache->key_to_node[1]->val == 7);
    assert(allocation_calls == calls && cache->min_freq == LFU_FREQ_SLOTS - 1);
    check_structure(cache); lfuFree(cache); assert(live_blocks == 0 && live_bytes == 0);
}

enum { MODEL_KEYS = 8 };
typedef struct { bool present; int val, freq; uint64_t used; } ModelItem;
typedef struct { int capacity, size; uint64_t clock; ModelItem items[MODEL_KEYS]; } Model;

static bool model_get(Model *model, int key, int *out) {
    ModelItem *item = &model->items[key];
    if (!item->present) return false;
    item->freq++; item->used = ++model->clock; *out = item->val; return true;
}
static void model_put(Model *model, int key, int value) {
    ModelItem *item = &model->items[key];
    if (!item->present) {
        if (model->size == model->capacity) {
            int victim = -1;
            for (int k = 0; k < MODEL_KEYS; k++) {
                ModelItem *candidate = &model->items[k];
                if (candidate->present && (victim == -1 || candidate->freq < model->items[victim].freq ||
                    (candidate->freq == model->items[victim].freq && candidate->used < model->items[victim].used))) victim = k;
            }
            assert(victim >= 0); model->items[victim].present = false; model->size--;
        }
        item->present = true; item->freq = 0; model->size++;
    }
    item->val = value; item->freq++; item->used = ++model->clock;
}
static void check_model(const LFUCache *cache, const Model *model) {
    int minimum = 0;
    assert(cache->size == model->size);
    for (int key = 0; key < MODEL_KEYS; key++) {
        const ModelItem *item = &model->items[key];
        const LFUNode *node = cache->key_to_node[key];
        assert((node != NULL) == item->present);
        if (item->present) {
            assert(node->val == item->val && node->freq == item->freq);
            if (minimum == 0 || item->freq < minimum) minimum = item->freq;
            /* Each frequency list is newest first, using independent timestamps. */
            uint64_t previous_use = UINT64_MAX;
            const LFUList *list = cache->freq_to_list[item->freq];
            for (const LFUNode *n = list->head->next; n != list->tail; n = n->next) {
                assert(n->key >= 0 && n->key < MODEL_KEYS && model->items[n->key].present);
                assert(model->items[n->key].used < previous_use);
                previous_use = model->items[n->key].used;
            }
        }
    }
    assert(cache->min_freq == minimum);
}

static void test_reference_oracle(void) {
    const int capacities[] = {1, 2, 4};
    for (size_t ci = 0; ci < sizeof(capacities) / sizeof(capacities[0]); ci++) {
        reset_allocator(); LFUCache *cache = lfuCreate(capacities[ci]); assert(cache);
        Model model = {0}; model.capacity = capacities[ci];
        uint32_t random = UINT32_C(0x460) + (uint32_t)ci;
        for (int operation = 0; operation < 3000; operation++) {
            random = random * UINT32_C(1664525) + UINT32_C(1013904223);
            int key = (int)((random >> 8) % MODEL_KEYS);
            if ((random >> 24) % 3U != 0) {
                int value = (int)((random >> 12) % 2001U) - 1000;
                assert(lfuTryPut(cache, key, value)); model_put(&model, key, value);
            } else {
                int expected = 123456, actual = 123456;
                bool found = model_get(&model, key, &expected);
                assert(lfuTryGet(cache, key, &actual) == found && actual == expected);
            }
            check_model(cache, &model);
            if (operation % 250 == 0) check_structure(cache);
        }
        check_structure(cache); lfuFree(cache); assert(live_blocks == 0 && live_bytes == 0);
    }
}

static LFUCache *three_frequency_fixture(void) {
    LFUCache *cache = lfuCreate(3); assert(cache); int out;
    assert(lfuTryPut(cache, 1, 10) && lfuTryPut(cache, 2, 20) && lfuTryPut(cache, 3, 30));
    assert(lfuTryGet(cache, 2, &out) && lfuTryGet(cache, 3, &out) && lfuTryGet(cache, 3, &out));
    check_structure(cache); assert(live_blocks == 13); return cache;
}
static void historical_outer_free_equivalent(LFUCache *cache) {
    /* Only the original destructor body, on an adapted valid fixture. The
       historical algorithm is not executed; this is not a paired benchmark. */
    LFU_FREE(cache);
}
static void test_teardown_comparison(void) {
    reset_allocator(); LFUCache *cache = three_frequency_fixture();
    historical_outer_free_equivalent(cache);
    assert(live_blocks == 12);
    assert(live_bytes == 3 * sizeof(LFUNode) + 3 * (sizeof(LFUList) + 2 * sizeof(LFUNode)));
    printf("Teardown-only fixture: historical outer-free body retains %zu tracked blocks; ", live_blocks);
    for (size_t i = 0; i < TRACK_SLOTS; i++) if (allocations[i].ptr != NULL) tracked_free(allocations[i].ptr);
    assert(live_blocks == 0 && live_bytes == 0);
    reset_allocator(); cache = three_frequency_fixture(); lfuFree(cache);
    assert(live_blocks == 0 && live_bytes == 0);
    puts("complete teardown retains 0.");
}

int main(void) {
    test_constructor_and_boundaries();
    test_canonical_eviction_and_updates();
    test_new_entry_failures();
    test_promotion_failures_and_existing_lists();
    test_frequency_guard();
    test_reference_oracle();
    test_teardown_comparison();
    puts("LFU checked ownership practice: seven assertion groups and 9000 oracle operations passed.");
    return 0;
}
#endif
