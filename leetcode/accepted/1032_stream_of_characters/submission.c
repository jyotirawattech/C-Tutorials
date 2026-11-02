#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    bool isWord;
    int children[26];
} TrieNode;

typedef struct {
    TrieNode* trie;
    int trie_size;
    char* stream;
    int stream_idx;
    int max_len;
} StreamChecker;

StreamChecker* streamCheckerCreate(char** words, int wordsSize) {
    StreamChecker* obj = (StreamChecker*)malloc(sizeof(StreamChecker));
    
    // Allocate the maximum theoretical nodes to avoid dynamic resizing
    obj->trie = (TrieNode*)calloc(400005, sizeof(TrieNode));
    obj->trie_size = 1; // Index 0 is the root
    obj->max_len = 0;

    for (int i = 0; i < wordsSize; ++i) {
        int len = strlen(words[i]);
        if (len > obj->max_len) {
            obj->max_len = len;
        }
        
        int curr = 0;
        // Insert backwards
        for (int j = len - 1; j >= 0; --j) {
            int idx = words[i][j] - 'a';
            if (obj->trie[curr].children[idx] == 0) {
                obj->trie[curr].children[idx] = obj->trie_size++;
            }
            curr = obj->trie[curr].children[idx];
        }
        obj->trie[curr].isWord = true;
    }

    // Allocate flat stream buffer. Constraints say max 40000 queries.
    obj->stream = (char*)malloc(40005 * sizeof(char));
    obj->stream_idx = 0;
    
    return obj;
}

bool streamCheckerQuery(StreamChecker* obj, char letter) {
    obj->stream[obj->stream_idx++] = letter;
    int curr = 0;
    
    // Traverse backwards bounded by max_len
    for (int i = obj->stream_idx - 1; i >= 0 && (obj->stream_idx - i) <= obj->max_len; --i) {
        int idx = obj->stream[i] - 'a';
        
        if (obj->trie[curr].children[idx] == 0) {
            return false;
        }
        curr = obj->trie[curr].children[idx];
        if (obj->trie[curr].isWord) {
            return true;
        }
    }
    return false;
}

void streamCheckerFree(StreamChecker* obj) {
    free(obj->trie);
    free(obj->stream);
    free(obj);
}