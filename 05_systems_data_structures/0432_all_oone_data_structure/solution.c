/*
 * All O`one: checked local ownership practice, November 2026.
 * AI-assisted adaptation of historical C submission 2029540776; not submitted.
 * The original Accepted source/date remains under leetcode/accepted/0432_*.
 * Same hash-index/ordered-frequency-bucket design, repaired lifetime/failure paths.
 * Single-threaded; callers supply a live object and valid NUL-terminated strings.
 * Define ALLONE_NO_TEST_MAIN to build the core without the test allocator/main.
 */
#include <assert.h>
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { HASH_SIZE = 100003, KEY_LIMIT = 10 };

#ifndef ALLONE_NO_TEST_MAIN
static void *tracked_malloc(size_t size);
static void *tracked_calloc(size_t count, size_t size);
static void tracked_free(void *ptr);
#define AO_MALLOC tracked_malloc
#define AO_CALLOC tracked_calloc
#define AO_FREE tracked_free
#else
#define AO_MALLOC malloc
#define AO_CALLOC calloc
#define AO_FREE free
#endif

typedef struct Bucket Bucket;
typedef struct HashNode HashNode;
struct HashNode {
    char key[KEY_LIMIT + 1];
    Bucket *bucket;
    HashNode *hash_next;             /* alias chain, not an owning list */
    HashNode *b_prev, *b_next;
};
struct Bucket {
    int count;
    HashNode *keys_head;             /* owns each member node exactly once */
    Bucket *prev, *next;
};
typedef struct {
    HashNode **table;                /* indexes nodes owned by buckets */
    Bucket *head, *tail;
} AllOne;

static bool valid_key(const char *key, size_t *length) {
    if (key == NULL) return false;
    for (size_t i = 0; i <= KEY_LIMIT; i++) {
        if (key[i] == '\0') {
            if (i == 0) return false;
            *length = i;
            return true;
        }
        if (i == KEY_LIMIT || key[i] < 'a' || key[i] > 'z') return false;
    }
    return false;
}

static unsigned int key_hash(const char *key) {
    unsigned int value = 5381U;
    for (size_t i = 0; key[i] != '\0'; i++) {
        value = value * 33U + (unsigned char)key[i];
    }
    return value % HASH_SIZE;
}

static HashNode *find_node(const AllOne *obj, const char *key) {
    for (HashNode *node = obj->table[key_hash(key)]; node; node = node->hash_next) {
        if (strcmp(node->key, key) == 0) return node;
    }
    return NULL;
}

static Bucket *new_bucket(int count) {
    Bucket *bucket = AO_MALLOC(sizeof(*bucket));
    if (bucket != NULL) *bucket = (Bucket){count, NULL, NULL, NULL};
    return bucket;
}

static void link_bucket_after(Bucket *before, Bucket *bucket) {
    bucket->prev = before;
    bucket->next = before->next;
    before->next->prev = bucket;
    before->next = bucket;
}

static void unlink_node(HashNode *node) {
    if (node->b_prev) node->b_prev->b_next = node->b_next;
    else node->bucket->keys_head = node->b_next;
    if (node->b_next) node->b_next->b_prev = node->b_prev;
    node->b_prev = node->b_next = NULL;
}

static void link_node(Bucket *bucket, HashNode *node) {
    node->bucket = bucket;
    node->b_prev = NULL;
    node->b_next = bucket->keys_head;
    if (bucket->keys_head) bucket->keys_head->b_prev = node;
    bucket->keys_head = node;
}

static void discard_empty_bucket(Bucket *bucket) {
    if (bucket->keys_head == NULL) {
        bucket->prev->next = bucket->next;
        bucket->next->prev = bucket->prev;
        AO_FREE(bucket);
    }
}

AllOne *allOneCreate(void) {
    AllOne *obj = AO_MALLOC(sizeof(*obj));
    if (obj == NULL) return NULL;
    *obj = (AllOne){NULL, NULL, NULL};
    obj->table = AO_CALLOC(HASH_SIZE, sizeof(*obj->table));
    if (obj->table == NULL) goto fail;
    obj->head = new_bucket(0);
    if (obj->head == NULL) goto fail;
    obj->tail = new_bucket(0);
    if (obj->tail == NULL) goto fail;
    obj->head->next = obj->tail;
    obj->tail->prev = obj->head;
    return obj;
fail:
    AO_FREE(obj->tail);
    AO_FREE(obj->head);
    AO_FREE(obj->table);
    AO_FREE(obj);
    return NULL;
}

/* false means invalid input, allocation failure or INT_MAX; state is unchanged. */
bool allOneTryInc(AllOne *obj, const char *key) {
    size_t length;
    if (obj == NULL || !valid_key(key, &length)) return false;
    HashNode *node = find_node(obj, key);
    if (node == NULL) {
        node = AO_MALLOC(sizeof(*node));
        if (node == NULL) return false;
        Bucket *target = obj->head->next;
        Bucket *prepared = NULL;
        if (target == obj->tail || target->count != 1) {
            prepared = new_bucket(1);
            if (prepared == NULL) { AO_FREE(node); return false; }
            target = prepared;
        }
        /* All allocations succeeded before publishing either ownership/alias. */
        for (size_t i = 0; i <= length; i++) node->key[i] = key[i];
        if (prepared) link_bucket_after(obj->head, prepared);
        unsigned int index = key_hash(key);
        node->hash_next = obj->table[index];
        obj->table[index] = node;
        link_node(target, node);
        return true;
    }
    Bucket *current = node->bucket;
    if (current->count == INT_MAX) return false;
    Bucket *target = current->next;
    if (target == obj->tail || target->count != current->count + 1) {
        target = new_bucket(current->count + 1);
        if (target == NULL) return false;
        link_bucket_after(current, target);
    }
    unlink_node(node);
    link_node(target, node);
    discard_empty_bucket(current);
    return true;
}

/* false means invalid/missing key or allocation failure; state is unchanged. */
bool allOneTryDec(AllOne *obj, const char *key) {
    size_t length;
    if (obj == NULL || !valid_key(key, &length)) return false;
    HashNode *node = find_node(obj, key);
    if (node == NULL) return false;
    Bucket *current = node->bucket;
    if (current->count == 1) {
        HashNode **link = &obj->table[key_hash(key)];
        while (*link != node) link = &(*link)->hash_next;
        *link = node->hash_next;
        unlink_node(node);
        AO_FREE(node);
    } else {
        Bucket *target = current->prev;
        if (target == obj->head || target->count != current->count - 1) {
            target = new_bucket(current->count - 1);
            if (target == NULL) return false; /* no unlink before allocation */
            link_bucket_after(current->prev, target);
        }
        unlink_node(node);
        link_node(target, node);
    }
    discard_empty_bucket(current);
    return true;
}

/* Borrowed read-only strings, valid only until the next mutation/free. */
const char *allOneGetMinKey(const AllOne *obj) {
    return obj == NULL || obj->head->next == obj->tail ? "" : obj->head->next->keys_head->key;
}
const char *allOneGetMaxKey(const AllOne *obj) {
    return obj == NULL || obj->head->next == obj->tail ? "" : obj->tail->prev->keys_head->key;
}

void allOneFree(AllOne *obj) {
    if (obj == NULL) return;
    Bucket *bucket = obj->head->next;
    while (bucket != obj->tail) {
        Bucket *next_bucket = bucket->next;
        HashNode *node = bucket->keys_head;
        while (node != NULL) {
            HashNode *next_node = node->b_next;
            AO_FREE(node);
            node = next_node;
        }
        AO_FREE(bucket);
        bucket = next_bucket;
    }
    AO_FREE(obj->head);
    AO_FREE(obj->tail);
    AO_FREE(obj->table);
    AO_FREE(obj);
}

#ifndef ALLONE_NO_TEST_MAIN
/* Bounded synthetic fault/tracking allocator; excluded from library builds. */
enum { TRACK_SLOTS = 256 };
typedef struct { void *ptr; size_t size; } Allocation;
static Allocation allocations[TRACK_SLOTS];
static size_t allocation_calls, fail_at, live_blocks, live_bytes;

static void *record_allocation(void *ptr, size_t size) {
    assert(ptr != NULL); /* real host OOM is not the synthetic failure mechanism */
    for (size_t i = 0; i < TRACK_SLOTS; i++) {
        if (allocations[i].ptr == NULL) {
            allocations[i] = (Allocation){ptr, size};
            live_blocks++;
            live_bytes += size;
            return ptr;
        }
    }
    assert(!"test allocation tracking capacity exceeded");
    abort();
}
static void *tracked_malloc(size_t size) {
    allocation_calls++;
    if (fail_at && allocation_calls == fail_at) return NULL;
    return record_allocation(malloc(size), size);
}
static void *tracked_calloc(size_t count, size_t size) {
    assert(size == 0 || count <= SIZE_MAX / size);
    allocation_calls++;
    if (fail_at && allocation_calls == fail_at) return NULL;
    return record_allocation(calloc(count, size), count * size);
}
static void tracked_free(void *ptr) {
    if (ptr == NULL) return;
    for (size_t i = 0; i < TRACK_SLOTS; i++) {
        if (allocations[i].ptr == ptr) {
            live_blocks--;
            live_bytes -= allocations[i].size;
            allocations[i] = (Allocation){NULL, 0};
            free(ptr);
            return;
        }
    }
    assert(!"untracked/double free");
    abort();
}
static void reset_allocator(void) {
    assert(live_blocks == 0 && live_bytes == 0);
    allocation_calls = fail_at = 0;
}
static void fail_nth_next(size_t nth) { fail_at = allocation_calls + nth; }
static void stop_failing(void) { fail_at = 0; }

static void check_structure(const AllOne *obj, size_t expected_keys) {
    assert(obj && obj->head && obj->tail && obj->table);
    assert(obj->head->prev == NULL && obj->tail->next == NULL);
    size_t keys = 0, buckets = 0;
    int previous_count = 0;
    const Bucket *previous = obj->head;
    for (const Bucket *b = obj->head->next; b != obj->tail; b = b->next) {
        assert(b && b->prev == previous && b->count > previous_count && b->keys_head);
        const HashNode *prior_key = NULL;
        for (const HashNode *n = b->keys_head; n; n = n->b_next) {
            assert(n->bucket == b && n->b_prev == prior_key);
            assert(find_node(obj, n->key) == n);
            prior_key = n;
            assert(++keys <= expected_keys);
        }
        previous_count = b->count;
        previous = b;
        assert(++buckets <= expected_keys);
    }
    assert(obj->tail->prev == previous && previous->next == obj->tail);
    assert(keys == expected_keys);
    assert(live_blocks == 4 + keys + buckets);
}
static int count_of(const AllOne *obj, const char *key) {
    HashNode *node = find_node(obj, key);
    return node ? node->bucket->count : 0;
}
static void check_hash_index(const AllOne *obj, size_t expected_keys) {
    size_t keys = 0;
    for (size_t i = 0; i < HASH_SIZE; i++) {
        for (const HashNode *n = obj->table[i]; n; n = n->hash_next) {
            assert(key_hash(n->key) == i);
            assert(++keys <= expected_keys);
        }
    }
    assert(keys == expected_keys);
}

static void test_constructor_failures(void) {
    for (size_t failure = 1; failure <= 4; failure++) {
        reset_allocator(); fail_nth_next(failure);
        assert(allOneCreate() == NULL);
        assert(live_blocks == 0 && live_bytes == 0);
    }
    reset_allocator();
    AllOne *obj = allOneCreate(); assert(obj);
    check_structure(obj, 0);
    assert(strcmp(allOneGetMinKey(obj), "") == 0);
    assert(strcmp(allOneGetMaxKey(obj), "") == 0);
    allOneFree(obj); allOneFree(NULL);
    assert(live_blocks == 0);
}

static void test_fixed_and_collision_cases(void) {
    reset_allocator();
    AllOne *obj = allOneCreate(); assert(obj);
    assert(!allOneTryDec(obj, "missing"));
    assert(allOneTryInc(obj, "apple"));
    assert(allOneTryInc(obj, "banana"));
    assert(allOneTryInc(obj, "banana"));
    assert(count_of(obj, allOneGetMinKey(obj)) == 1);
    assert(strcmp(allOneGetMaxKey(obj), "banana") == 0);
    const char *borrowed = allOneGetMaxKey(obj);
    assert(borrowed == find_node(obj, "banana")->key);
    assert(strcmp(borrowed, "banana") == 0); /* use only before mutation */
    assert(allOneTryDec(obj, "banana"));
    assert(count_of(obj, allOneGetMaxKey(obj)) == 1);
    assert(allOneTryDec(obj, "apple"));
    assert(strcmp(allOneGetMinKey(obj), "banana") == 0);
    assert(allOneTryDec(obj, "banana"));
    check_structure(obj, 0);
    assert(key_hash("ahfu") == key_hash("daaa"));
    assert(key_hash("daaa") == key_hash("llqg"));
    assert(allOneTryInc(obj, "ahfu")); assert(allOneTryInc(obj, "daaa"));
    assert(allOneTryInc(obj, "llqg"));
    check_structure(obj, 3); check_hash_index(obj, 3);
    assert(allOneTryDec(obj, "daaa")); /* remove collision chain middle */
    assert(find_node(obj, "daaa") == NULL && find_node(obj, "ahfu") != NULL);
    assert(find_node(obj, "llqg") != NULL);
    assert(allOneTryDec(obj, "llqg")); /* remove collision chain head */
    assert(find_node(obj, "llqg") == NULL && find_node(obj, "ahfu") != NULL);
    assert(allOneTryDec(obj, "ahfu")); /* remove final collision entry */
    check_structure(obj, 0); check_hash_index(obj, 0);
    allOneFree(obj); assert(live_blocks == 0);
}

static void test_invalid_keys_and_overflow(void) {
    reset_allocator();
    AllOne *obj = allOneCreate(); assert(obj);
    const char *bad[] = {NULL, "", "Upper", "with-space", "elevenchars", "a1"};
    assert(!allOneTryInc(NULL, "a") && !allOneTryDec(NULL, "a"));
    assert(strcmp(allOneGetMinKey(NULL), "") == 0);
    for (size_t i = 0; i < sizeof(bad) / sizeof(bad[0]); i++) {
        size_t calls = allocation_calls;
        assert(!allOneTryInc(obj, bad[i]) && !allOneTryDec(obj, bad[i]));
        assert(allocation_calls == calls);
        check_structure(obj, 0);
    }
    assert(allOneTryInc(obj, "abcdefghij"));
    HashNode *node = find_node(obj, "abcdefghij");
    node->bucket->count = INT_MAX; /* synthetic otherwise unreachable boundary */
    size_t calls = allocation_calls;
    assert(!allOneTryInc(obj, "abcdefghij"));
    assert(node->bucket->count == INT_MAX && allocation_calls == calls);
    check_structure(obj, 1);
    allOneFree(obj); assert(live_blocks == 0);
}

static void test_operation_allocation_failures(void) {
    for (size_t failure = 1; failure <= 2; failure++) {
        reset_allocator();
        AllOne *obj = allOneCreate(); assert(obj);
        fail_nth_next(failure);
        assert(!allOneTryInc(obj, "new"));
        stop_failing(); check_structure(obj, 0); check_hash_index(obj, 0);
        assert(live_blocks == 4);
        assert(allOneTryInc(obj, "new"));
        check_structure(obj, 1);
        allOneFree(obj); assert(live_blocks == 0);
    }
    reset_allocator();
    AllOne *obj = allOneCreate(); assert(obj);
    assert(allOneTryInc(obj, "a")); assert(allOneTryInc(obj, "b"));
    Bucket *old_bucket = find_node(obj, "a")->bucket;
    size_t blocks = live_blocks;
    fail_nth_next(1); assert(!allOneTryInc(obj, "a"));
    stop_failing(); assert(find_node(obj, "a")->bucket == old_bucket);
    assert(count_of(obj, "a") == 1 && count_of(obj, "b") == 1 && live_blocks == blocks);
    check_structure(obj, 2);
    assert(allOneTryInc(obj, "a")); assert(allOneTryInc(obj, "a"));
    old_bucket = find_node(obj, "a")->bucket; blocks = live_blocks;
    fail_nth_next(1); assert(!allOneTryDec(obj, "a"));
    stop_failing(); assert(find_node(obj, "a")->bucket == old_bucket);
    assert(count_of(obj, "a") == 3 && count_of(obj, "b") == 1 && live_blocks == blocks);
    check_structure(obj, 2); check_hash_index(obj, 2);
    /* A count=1 bucket already exists: allocation failure must not add a node. */
    fail_nth_next(1); assert(!allOneTryInc(obj, "c"));
    stop_failing(); assert(find_node(obj, "c") == NULL); check_structure(obj, 2);
    /* Moves into an existing bucket require no allocation. */
    assert(allOneTryDec(obj, "a"));
    fail_nth_next(1); size_t calls = allocation_calls;
    assert(allOneTryDec(obj, "a"));
    assert(allocation_calls == calls); stop_failing();
    check_structure(obj, 2);
    allOneFree(obj); assert(live_blocks == 0);
}

static void test_reference_oracle(void) {
    static const char *keys[] = {"a", "b", "c", "d", "ahfu", "daaa", "abcdef", "abcdefghij"};
    enum { KEY_COUNT = sizeof(keys) / sizeof(keys[0]), OPERATIONS = 8000 };
    int reference[KEY_COUNT] = {0};
    uint32_t random = 0x432U;
    reset_allocator();
    AllOne *obj = allOneCreate(); assert(obj);
    for (int operation = 0; operation < OPERATIONS; operation++) {
        random = random * UINT32_C(1664525) + UINT32_C(1013904223);
        size_t selected = (random >> 8) % KEY_COUNT;
        if (random & 1U) {
            assert(allOneTryInc(obj, keys[selected])); reference[selected]++;
        } else {
            bool expected = reference[selected] > 0;
            assert(allOneTryDec(obj, keys[selected]) == expected);
            if (expected) reference[selected]--;
        }
        size_t distinct = 0;
        int minimum = INT_MAX, maximum = 0;
        for (size_t k = 0; k < KEY_COUNT; k++) {
            assert(count_of(obj, keys[k]) == reference[k]);
            if (reference[k]) {
                distinct++;
                if (reference[k] < minimum) minimum = reference[k];
                if (reference[k] > maximum) maximum = reference[k];
            }
        }
        check_structure(obj, distinct);
        if (distinct) {
            assert(count_of(obj, allOneGetMinKey(obj)) == minimum);
            assert(count_of(obj, allOneGetMaxKey(obj)) == maximum);
        } else {
            assert(allOneGetMinKey(obj)[0] == '\0' && allOneGetMaxKey(obj)[0] == '\0');
        }
        if (operation % 500 == 0) check_hash_index(obj, distinct);
    }
    allOneFree(obj); assert(live_blocks == 0 && live_bytes == 0);
}

static AllOne *three_key_fixture(void) {
    AllOne *obj = allOneCreate(); assert(obj);
    assert(allOneTryInc(obj, "a"));
    assert(allOneTryInc(obj, "b")); assert(allOneTryInc(obj, "b"));
    assert(allOneTryInc(obj, "c")); assert(allOneTryInc(obj, "c")); assert(allOneTryInc(obj, "c"));
    check_structure(obj, 3); assert(live_blocks == 10);
    return obj;
}

static void historical_teardown_equivalent(AllOne *obj) {
    /* Exactly the original four-free body, on an adapted preconstructed fixture.
       This is a teardown-only comparator, not execution of the original program. */
    AO_FREE(obj->head); AO_FREE(obj->tail); AO_FREE(obj->table); AO_FREE(obj);
}

static void test_teardown_comparison(void) {
    reset_allocator();
    AllOne *obj = three_key_fixture();
    historical_teardown_equivalent(obj);
    assert(live_blocks == 6);
    assert(live_bytes == 3 * sizeof(HashNode) + 3 * sizeof(Bucket));
    printf("Teardown-only fixture: historical four-free body retains %zu tracked blocks; ", live_blocks);
    /* Quarantine cleanup keeps the known-baseline reproduction from leaking. */
    for (size_t i = 0; i < TRACK_SLOTS; i++) {
        if (allocations[i].ptr) tracked_free(allocations[i].ptr);
    }
    assert(live_blocks == 0 && live_bytes == 0);
    reset_allocator(); obj = three_key_fixture(); allOneFree(obj);
    assert(live_blocks == 0 && live_bytes == 0);
    puts("repaired teardown retains 0.");
}

int main(void) {
    test_constructor_failures();
    test_fixed_and_collision_cases();
    test_invalid_keys_and_overflow();
    test_operation_allocation_failures();
    test_reference_oracle();
    test_teardown_comparison();
    puts("All O`one ownership adaptation: six test groups and 8000 oracle operations passed.");
    return 0;
}
#endif
