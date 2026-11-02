#include <stdlib.h>
#include <stdbool.h>

#define HASH_SIZE 100003 // A large prime number to minimize collisions

// Node for our Separate Chaining Hash Map
typedef struct HashNode {
    int key;
    int arr_idx; // Maps the value to its index in the dynamic array
    struct HashNode* next;
} HashNode;

typedef struct {
    int* nums;          // The dynamic array for O(1) GetRandom
    int size;
    int capacity;
    HashNode** buckets; // The Hash Map
} RandomizedSet;

// Helper: Fast hashing function that handles negative numbers
int hash(int key) {
    int h = key % HASH_SIZE;
    return h < 0 ? h + HASH_SIZE : h;
}

RandomizedSet* randomizedSetCreate() {
    RandomizedSet* obj = (RandomizedSet*)malloc(sizeof(RandomizedSet));
    
    // Pre-allocate the maximum constraints
    obj->capacity = 200005;
    obj->nums = (int*)malloc(obj->capacity * sizeof(int));
    obj->size = 0;
    
    // Initialize Hash Map buckets to NULL
    obj->buckets = (HashNode**)calloc(HASH_SIZE, sizeof(HashNode*));
    
    return obj;
}

bool randomizedSetInsert(RandomizedSet* obj, int val) {
    int h = hash(val);
    HashNode* curr = obj->buckets[h];
    
    // Check if it already exists
    while (curr != NULL) {
        if (curr->key == val) return false;
        curr = curr->next;
    }
    
    // 1. Add to the dynamic array
    obj->nums[obj->size] = val;
    
    // 2. Add to the Hash Map (Insert at the head of the linked list)
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->key = val;
    newNode->arr_idx = obj->size;
    newNode->next = obj->buckets[h];
    obj->buckets[h] = newNode;
    
    obj->size++;
    return true;
}

bool randomizedSetRemove(RandomizedSet* obj, int val) {
    int h = hash(val);
    HashNode* curr = obj->buckets[h];
    HashNode* prev = NULL;
    
    // Search for the node in the Hash Map
    while (curr != NULL && curr->key != val) {
        prev = curr;
        curr = curr->next;
    }
    
    if (curr == NULL) return false; // Not found
    
    // We found it! Grab the array index we need to delete
    int idxToRemove = curr->arr_idx;
    int lastVal = obj->nums[obj->size - 1];
    
    // --- SWAP AND POP LOGIC ---
    // Overwrite the target with the last element
    obj->nums[idxToRemove] = lastVal;
    
    // We must update the Hash Map entry for the swapped `lastVal`
    if (idxToRemove != obj->size - 1) {
        int lastH = hash(lastVal);
        HashNode* updateNode = obj->buckets[lastH];
        while (updateNode->key != lastVal) {
            updateNode = updateNode->next;
        }
        updateNode->arr_idx = idxToRemove; // Give it the new index
    }
    
    // --- CLEAN UP THE HASH MAP ---
    // Remove the original target node from its linked list
    if (prev == NULL) {
        obj->buckets[h] = curr->next; // It was the head
    } else {
        prev->next = curr->next;      // It was in the middle
    }
    free(curr); // Prevent memory leak
    
    obj->size--;
    return true;
}

int randomizedSetGetRandom(RandomizedSet* obj) {
    // Generate a random index within the current bounds
    return obj->nums[rand() % obj->size];
}

void randomizedSetFree(RandomizedSet* obj) {
    // Free the linked lists to prevent memory leaks
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* curr = obj->buckets[i];
        while (curr != NULL) {
            HashNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(obj->buckets);
    free(obj->nums);
    free(obj);
}