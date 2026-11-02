/**
 * Problem: LeetCode 0208 - Implement Trie (Prefix Tree)
 * Language: C (C11)
 *
 * Approach:
 * Implements a 26-ary prefix tree (Trie) in pure C.
 * Widely used in networking routing tables (IP prefix lookup), DNS resolvers,
 * autocompletion engines, and packet classification pipelines.
 *
 * Complexity:
 * - Time: O(L) for insert, search, and startsWith, where L is the key length.
 * - Space: O(N * ALPHABET_SIZE) where N is the total number of characters stored.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define ALPHABET_SIZE 26

typedef struct Trie {
    struct Trie* children[ALPHABET_SIZE];
    bool is_end_of_word;
} Trie;

Trie* trieCreate(void) {
    Trie* node = (Trie*)malloc(sizeof(Trie));
    if (!node) return NULL;
    node->is_end_of_word = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void trieInsert(Trie* obj, const char* word) {
    if (!obj || !word) return;

    Trie* curr = obj;
    for (int i = 0; word[i] != '\0'; i++) {
        int idx = word[i] - 'a';
        if (idx < 0 || idx >= ALPHABET_SIZE) continue;

        if (curr->children[idx] == NULL) {
            curr->children[idx] = trieCreate();
        }
        curr = curr->children[idx];
    }
    curr->is_end_of_word = true;
}

bool trieSearch(Trie* obj, const char* word) {
    if (!obj || !word) return false;

    Trie* curr = obj;
    for (int i = 0; word[i] != '\0'; i++) {
        int idx = word[i] - 'a';
        if (idx < 0 || idx >= ALPHABET_SIZE || curr->children[idx] == NULL) {
            return false;
        }
        curr = curr->children[idx];
    }
    return curr != NULL && curr->is_end_of_word;
}

bool trieStartsWith(Trie* obj, const char* prefix) {
    if (!obj || !prefix) return false;

    Trie* curr = obj;
    for (int i = 0; prefix[i] != '\0'; i++) {
        int idx = prefix[i] - 'a';
        if (idx < 0 || idx >= ALPHABET_SIZE || curr->children[idx] == NULL) {
            return false;
        }
        curr = curr->children[idx];
    }
    return true;
}

void trieFree(Trie* obj) {
    if (!obj) return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (obj->children[i] != NULL) {
            trieFree(obj->children[i]);
        }
    }
    free(obj);
}

/* ========================================================================= */
/* Standalone Test Harness                                                   */
/* ========================================================================= */

int main(void) {
    printf("[TEST] Running LeetCode 0208: Implement Trie...\n");

    // Test Case: Standard LeetCode Sequence
    // Trie trie = new Trie();
    // trie.insert("apple");
    // trie.search("apple");   // return True
    // trie.search("app");     // return False
    // trie.startsWith("app"); // return True
    // trie.insert("app");
    // trie.search("app");     // return True

    Trie* trie = trieCreate();
    assert(trie != NULL);

    trieInsert(trie, "apple");
    assert(trieSearch(trie, "apple") == true);
    printf("  ✓ search(\"apple\") -> true\n");

    assert(trieSearch(trie, "app") == false);
    printf("  ✓ search(\"app\") -> false\n");

    assert(trieStartsWith(trie, "app") == true);
    printf("  ✓ startsWith(\"app\") -> true\n");

    trieInsert(trie, "app");
    assert(trieSearch(trie, "app") == true);
    printf("  ✓ search(\"app\") after insert -> true\n");

    assert(trieSearch(trie, "orange") == false);
    assert(trieStartsWith(trie, "ora") == false);
    printf("  ✓ search(\"orange\") & startsWith(\"ora\") -> false\n");

    trieFree(trie);

    printf("[PASSED] All LeetCode 0208 tests passed with zero leaks!\n\n");
    return 0;
}
