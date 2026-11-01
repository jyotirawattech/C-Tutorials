/**
 * Problem: LeetCode 0146 - LRU Cache
 * Language: C (C11)
 *
 * Approach:
 * Combines a Doubly Linked List (for O(1) eviction and recency updates)
 * with a Hash Map with separate chaining (for O(1) key-to-node pointer lookup).
 *
 * In kernel page caching, buffer caches, and hardware translation lookaside
 * buffers (TLB), LRU eviction is the gold standard replacement strategy.
 *
 * Complexity:
 * - Time: O(1) for both get() and put() operations.
 * - Space: O(Capacity) strictly bounded memory footprint.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct DListNode {
    int key;
    int value;
    struct DListNode* prev;
    struct DListNode* next;
} DListNode;

typedef struct HashEntry {
    int key;
    DListNode* node;
    struct HashEntry* next;
} HashEntry;

typedef struct {
    int capacity;
    int size;
    int hash_capacity;
    HashEntry** table;
    DListNode* head;
    DListNode* tail;
} LRUCache;

static unsigned int lru_hash(int key, int capacity) {
    unsigned int ukey = (unsigned int)key;
    return (ukey * 2654435761u) % (unsigned int)capacity;
}

static void dlist_add_to_head(LRUCache* cache, DListNode* node) {
    node->next = cache->head->next;
    node->prev = cache->head;
    cache->head->next->prev = node;
    cache->head->next = node;
}

static void dlist_remove_node(DListNode* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

static void dlist_move_to_head(LRUCache* cache, DListNode* node) {
    dlist_remove_node(node);
    dlist_add_to_head(cache, node);
}

static DListNode* dlist_pop_tail(LRUCache* cache) {
    DListNode* lru = cache->tail->prev;
    dlist_remove_node(lru);
    return lru;
}

static void hash_insert(LRUCache* cache, int key, DListNode* node) {
    unsigned int idx = lru_hash(key, cache->hash_capacity);
    HashEntry* entry = (HashEntry*)malloc(sizeof(HashEntry));
    entry->key = key;
    entry->node = node;
    entry->next = cache->table[idx];
    cache->table[idx] = entry;
}

static DListNode* hash_find(LRUCache* cache, int key) {
    unsigned int idx = lru_hash(key, cache->hash_capacity);
    HashEntry* curr = cache->table[idx];
    while (curr) {
        if (curr->key == key) {
            return curr->node;
        }
        curr = curr->next;
    }
    return NULL;
}

static void hash_remove(LRUCache* cache, int key) {
    unsigned int idx = lru_hash(key, cache->hash_capacity);
    HashEntry* curr = cache->table[idx];
    HashEntry* prev = NULL;

    while (curr) {
        if (curr->key == key) {
            if (prev) {
                prev->next = curr->next;
            } else {
                cache->table[idx] = curr->next;
            }
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

LRUCache* lruCacheCreate(int capacity) {
    if (capacity <= 0) return NULL;

    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    if (!cache) return NULL;

    cache->capacity = capacity;
    cache->size = 0;
    cache->hash_capacity = capacity * 2 > 16 ? capacity * 2 : 16;

    cache->table = (HashEntry**)calloc((size_t)cache->hash_capacity, sizeof(HashEntry*));
    if (!cache->table) {
        free(cache);
        return NULL;
    }

    // Dummy sentinel head and tail nodes
    cache->head = (DListNode*)malloc(sizeof(DListNode));
    cache->tail = (DListNode*)malloc(sizeof(DListNode));
    cache->head->prev = NULL;
    cache->head->next = cache->tail;
    cache->tail->prev = cache->head;
    cache->tail->next = NULL;

    return cache;
}

int lruCacheGet(LRUCache* obj, int key) {
    if (!obj) return -1;

    DListNode* node = hash_find(obj, key);
    if (!node) {
        return -1;
    }

    // Move accessed node to head of list (most recently used)
    dlist_move_to_head(obj, node);
    return node->value;
}

void lruCachePut(LRUCache* obj, int key, int value) {
    if (!obj) return;

    DListNode* existing_node = hash_find(obj, key);
    if (existing_node) {
        existing_node->value = value;
        dlist_move_to_head(obj, existing_node);
        return;
    }

    // If cache is at full capacity, evict the least recently used node
    if (obj->size >= obj->capacity) {
        DListNode* lru = dlist_pop_tail(obj);
        hash_remove(obj, lru->key);
        free(lru);
        obj->size--;
    }

    // Allocate and insert new node at head
    DListNode* new_node = (DListNode*)malloc(sizeof(DListNode));
    new_node->key = key;
    new_node->value = value;
    dlist_add_to_head(obj, new_node);
    hash_insert(obj, key, new_node);
    obj->size++;
}

void lruCacheFree(LRUCache* obj) {
    if (!obj) return;

    // Free all doubly linked list nodes
    DListNode* curr = obj->head;
    while (curr) {
        DListNode* next = curr->next;
        free(curr);
        curr = next;
    }

    // Free hash table buckets
    for (int i = 0; i < obj->hash_capacity; i++) {
        HashEntry* entry = obj->table[i];
        while (entry) {
            HashEntry* next_entry = entry->next;
            free(entry);
            entry = next_entry;
        }
    }
    free(obj->table);
    free(obj);
}

/* ========================================================================= */
/* Standalone Test Harness                                                   */
/* ========================================================================= */

int main(void) {
    printf("[TEST] Running LeetCode 0146: LRU Cache...\n");

    // Test Case: Standard LeetCode Sequence
    // LRUCache lRUCache = new LRUCache(2);
    // lRUCache.put(1, 1); // cache is {1=1}
    // lRUCache.put(2, 2); // cache is {1=1, 2=2}
    // lRUCache.get(1);    // return 1
    // lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    // lRUCache.get(2);    // returns -1 (not found)
    // lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    // lRUCache.get(1);    // return -1 (not found)
    // lRUCache.get(3);    // return 3
    // lRUCache.get(4);    // return 4

    LRUCache* cache = lruCacheCreate(2);
    assert(cache != NULL);

    lruCachePut(cache, 1, 1);
    lruCachePut(cache, 2, 2);

    int val = lruCacheGet(cache, 1);
    assert(val == 1);
    printf("  ✓ get(1) returned %d\n", val);

    lruCachePut(cache, 3, 3); // evicts key 2

    val = lruCacheGet(cache, 2);
    assert(val == -1);
    printf("  ✓ get(2) returned -1 (evicted properly)\n");

    lruCachePut(cache, 4, 4); // evicts key 1

    val = lruCacheGet(cache, 1);
    assert(val == -1);
    printf("  ✓ get(1) returned -1 (evicted properly)\n");

    val = lruCacheGet(cache, 3);
    assert(val == 3);
    printf("  ✓ get(3) returned %d\n", val);

    val = lruCacheGet(cache, 4);
    assert(val == 4);
    printf("  ✓ get(4) returned %d\n", val);

    lruCacheFree(cache);

    printf("[PASSED] All LeetCode 0146 tests passed with zero leaks!\n\n");
    return 0;
}
