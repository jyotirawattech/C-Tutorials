/*
 * LeetCode 208 practice adaptation: checked lowercase trie (C11).
 * AI-assisted improvement, 2026-11-14; platform acceptance Not captured.
 * Insertion validates first, constructs a detached suffix, then commits once.
 * Root owns all allocations through owned_next; rollback/free use no recursion.
 */
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26

/* Override both hooks together for another allocator. Default main uses tests. */
#ifndef TRIE_NO_TEST_MAIN
static void *test_allocate(size_t bytes);
static void test_release(void *pointer);
#define TRIE_MALLOC test_allocate
#define TRIE_FREE test_release
#else
#ifndef TRIE_MALLOC
#define TRIE_MALLOC malloc
#endif
#ifndef TRIE_FREE
#define TRIE_FREE free
#endif
#endif

typedef struct Trie {
    struct Trie *children[ALPHABET_SIZE];
    bool is_end_of_word;
    struct Trie *owned_next;
} Trie;

static Trie *node_create(void) {
    Trie *node = TRIE_MALLOC(sizeof *node);
    if (!node) return NULL;
    for (size_t i = 0; i < ALPHABET_SIZE; ++i) node->children[i] = NULL;
    node->is_end_of_word = false;
    node->owned_next = NULL;
    return node;
}

static void release_chain(Trie *node) {
    while (node) {
        Trie *next = node->owned_next;
        TRIE_FREE(node);
        node = next;
    }
}

/* C-string arguments must point to readable NUL-terminated storage. */
static bool valid_key(const char *key) {
    if (!key) return false;
    for (const unsigned char *p = (const unsigned char *)key; *p; ++p) {
        if (*p < (unsigned char)'a' || *p > (unsigned char)'z') return false;
    }
    return true;
}

Trie *trieCreate(void) { return node_create(); }

/* Use only the owning root returned by trieCreate, never an interior node. */
bool trieInsert(Trie *root, const char *word) {
    if (!root || !valid_key(word)) return false;
    Trie *current = root;
    size_t offset = 0;
    while (word[offset]) {
        size_t index = (size_t)(word[offset] - 'a');
        if (!current->children[index]) break;
        current = current->children[index];
        ++offset;
    }
    if (!word[offset]) {
        current->is_end_of_word = true;
        return true;
    }

    const size_t attach_index = (size_t)(word[offset] - 'a');
    Trie *first = NULL, *last = NULL, *pending = NULL;
    for (; word[offset]; ++offset) {
        Trie *fresh = node_create();
        if (!fresh) {
            release_chain(pending);
            return false;
        }
        fresh->owned_next = pending;
        pending = fresh;
        if (last) last->children[(size_t)(word[offset] - 'a')] = fresh;
        else first = fresh;
        last = fresh;
    }
    last->is_end_of_word = true;
    /* first is the tail of the reversed ownership chain. No fallible step left. */
    first->owned_next = root->owned_next;
    root->owned_next = pending;
    current->children[attach_index] = first;
    return true;
}

static const Trie *find_prefix(const Trie *root, const char *key) {
    if (!root || !valid_key(key)) return NULL;
    const Trie *node = root;
    for (size_t i = 0; key[i]; ++i) {
        node = node->children[(size_t)(key[i] - 'a')];
        if (!node) return NULL;
    }
    return node;
}

bool trieSearch(const Trie *root, const char *word) {
    const Trie *node = find_prefix(root, word);
    return node && node->is_end_of_word;
}

bool trieStartsWith(const Trie *root, const char *prefix) {
    return find_prefix(root, prefix) != NULL;
}

void trieFree(Trie *root) {
    if (!root) return;
    release_chain(root->owned_next);
    TRIE_FREE(root);
}

#ifndef TRIE_NO_TEST_MAIN
static size_t live_blocks, attempts, fail_after = SIZE_MAX;

static void *test_allocate(size_t bytes) {
    ++attempts;
    if (fail_after == 0) return NULL;
    if (fail_after != SIZE_MAX) --fail_after;
    void *result = malloc(bytes);
    if (result) ++live_blocks;
    return result;
}

static void test_release(void *pointer) {
    if (!pointer) return;
    assert(live_blocks > 0);
    --live_blocks;
    free(pointer);
}

static void reset_allocator(void) {
    assert(live_blocks == 0);
    attempts = 0;
    fail_after = SIZE_MAX;
}

/* Test snapshot includes every existing node's links, terminal bit and identity. */
static uintptr_t snapshot(const Trie *root) {
    uintptr_t hash = 17;
    for (const Trie *node = root; node; node = node->owned_next) {
        hash = hash * 31u + (uintptr_t)node;
        hash = hash * 31u + (uintptr_t)node->owned_next;
        hash = hash * 31u + (uintptr_t)node->is_end_of_word;
        for (size_t i = 0; i < ALPHABET_SIZE; ++i)
            hash = hash * 31u + (uintptr_t)node->children[i];
    }
    return hash;
}

static void test_normal(void) {
    reset_allocator();
    Trie *root = trieCreate(); assert(root);
    assert(trieInsert(root, "apple"));
    assert(trieSearch(root, "apple"));
    assert(!trieSearch(root, "app"));
    assert(trieStartsWith(root, "app"));
    assert(trieInsert(root, "app"));
    assert(trieInsert(root, "ape"));
    assert(trieInsert(root, "z"));
    assert(trieSearch(root, "app") && trieSearch(root, "ape"));
    assert(!trieSearch(root, "apples") && !trieStartsWith(root, "b"));
    trieFree(root); assert(live_blocks == 0);
}

static void test_invalid(void) {
    reset_allocator();
    Trie *root = trieCreate(); assert(root);
    assert(trieInsert(root, "safe"));
    const char high[] = {'a', (char)0xff, 'b', '\0'};
    const char *invalid[] = {"ab#c", "UPPER", "a b", "a0", "!", high, NULL};
    uintptr_t before = snapshot(root);
    size_t blocks = live_blocks, calls = attempts;
    for (size_t i = 0; i < sizeof invalid / sizeof invalid[0]; ++i) {
        assert(!trieInsert(root, invalid[i]));
        assert(!trieSearch(root, invalid[i]));
        assert(!trieStartsWith(root, invalid[i]));
        assert(snapshot(root) == before && live_blocks == blocks && attempts == calls);
    }
    assert(!trieStartsWith(root, "ab") && !trieSearch(root, "abc"));
    assert(!trieInsert(NULL, "a") && !trieSearch(NULL, "a"));
    assert(!trieStartsWith(NULL, "") && trieSearch(root, "safe"));
    trieFree(root); trieFree(NULL); assert(live_blocks == 0);
}

static void test_failures(void) {
    reset_allocator();
    fail_after = 0;
    assert(trieCreate() == NULL && live_blocks == 0);
    /* Existing "car"/"dog" branches; candidate "cartoon" needs four nodes. */
    for (size_t fail = 0; fail <= 4; ++fail) {
        reset_allocator();
        Trie *root = trieCreate(); assert(root);
        assert(trieInsert(root, "car") && trieInsert(root, "dog"));
        uintptr_t before = snapshot(root);
        size_t blocks = live_blocks;
        fail_after = fail;
        bool inserted = trieInsert(root, "cartoon");
        fail_after = SIZE_MAX;
        assert(inserted == (fail == 4));
        assert(trieSearch(root, "car") && trieSearch(root, "dog"));
        if (!inserted) {
            assert(snapshot(root) == before && live_blocks == blocks);
            assert(!trieStartsWith(root, "cart"));
            assert(trieInsert(root, "cartoon"));
        }
        assert(trieSearch(root, "cartoon"));
        trieFree(root); assert(live_blocks == 0);
    }
    /* A root-only trie needs all six nodes; fail each detached-chain position. */
    for (size_t fail = 0; fail < 6; ++fail) {
        reset_allocator();
        Trie *root = trieCreate(); assert(root);
        uintptr_t before = snapshot(root);
        fail_after = fail;
        assert(!trieInsert(root, "abcdef"));
        assert(snapshot(root) == before && live_blocks == 1);
        assert(!trieStartsWith(root, "a"));
        fail_after = SIZE_MAX;
        trieFree(root); assert(live_blocks == 0);
    }
}

static void test_no_allocation(void) {
    reset_allocator();
    Trie *root = trieCreate(); assert(root);
    assert(trieInsert(root, "alphabet"));
    size_t calls = attempts;
    fail_after = 0;
    assert(trieInsert(root, "alphabet") && trieInsert(root, "alpha"));
    assert(trieSearch(root, "alpha") && trieStartsWith(root, "alph"));
    assert(attempts == calls);
    fail_after = SIZE_MAX;
    trieFree(root); assert(live_blocks == 0);
}

static void test_empty(void) {
    reset_allocator();
    Trie *root = trieCreate(); assert(root);
    assert(trieStartsWith(root, "") && !trieSearch(root, ""));
    fail_after = 0;
    assert(trieInsert(root, "") && trieSearch(root, ""));
    assert(trieInsert(root, ""));
    fail_after = SIZE_MAX;
    trieFree(root); assert(live_blocks == 0);
}

static void encode_word(size_t id, char word[6]) {
    for (size_t i = 0; i < 5; ++i) { word[i] = (char)('a' + id % 3); id /= 3; }
    word[5] = '\0';
}

static void test_oracle(void) {
    reset_allocator();
    bool present[243] = {false};
    Trie *root = trieCreate(); assert(root);
    uint32_t state = 208;
    for (size_t operation = 0; operation < 9000; ++operation) {
        state = state * UINT32_C(1664525) + UINT32_C(1013904223);
        size_t id = (state >> 8) % 243;
        char word[6]; encode_word(id, word);
        unsigned mode = state % 3;
        if (mode == 0) { assert(trieInsert(root, word)); present[id] = true; }
        else if (mode == 1) assert(trieSearch(root, word) == present[id]);
        else {
            size_t length = (state >> 16) % 6;
            word[length] = '\0';
            bool expected = length == 0; /* The root is always an empty prefix. */
            for (size_t other = 0; other < 243 && !expected; ++other) {
                if (!present[other]) continue;
                char candidate[6]; encode_word(other, candidate);
                bool equal = true;
                for (size_t i = 0; i < length; ++i)
                    if (candidate[i] != word[i]) { equal = false; break; }
                if (equal) expected = true;
            }
            assert(trieStartsWith(root, word) == expected);
        }
    }
    for (size_t id = 0; id < 243; ++id) {
        char word[6]; encode_word(id, word);
        assert(trieSearch(root, word) == present[id]);
    }
    trieFree(root); assert(live_blocks == 0);
}

static void test_deep_cleanup(void) {
    reset_allocator();
    const size_t length = 20000;
    char *word = malloc(length + 1); assert(word);
    for (size_t i = 0; i < length; ++i) word[i] = 'a';
    word[length] = '\0';
    Trie *root = trieCreate(); assert(root);
    assert(trieInsert(root, word) && trieSearch(root, word));
    assert(live_blocks == length + 1);
    trieFree(root); free(word); assert(live_blocks == 0);
}

int main(void) {
    test_normal(); test_invalid(); test_failures(); test_no_allocation();
    test_empty(); test_oracle(); test_deep_cleanup();
    puts("[PASSED] Trie: 7 groups, 9000 oracle operations, 10 failed suffix positions, zero tracked blocks retained.");
    return 0;
}
#endif
