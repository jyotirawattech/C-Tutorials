#include <stdlib.h>
#include <stdbool.h>

#define HASH_SIZE 100003 // Prime number to reduce collisions

typedef struct HashNode {
    int key;
    int arr_idx;
    struct HashNode* next;
} HashNode;

typedef struct {
    int* nums;
    int size;
    int capacity;
    HashNode** buckets;
} RandomizedCollection;

int hash(int key) {
    int h = key % HASH_SIZE;
    return h < 0 ? h + HASH_SIZE : h;
}

RandomizedCollection* randomizedCollectionCreate() {
    RandomizedCollection* obj = (RandomizedCollection*)malloc(sizeof(RandomizedCollection));
    obj->capacity = 200005;
    obj->nums = (int*)malloc(obj->capacity * sizeof(int));
    obj->size = 0;
    obj->buckets = (HashNode**)calloc(HASH_SIZE, sizeof(HashNode*));
    return obj;
}

bool randomizedCollectionInsert(RandomizedCollection* obj, int val) {
    int h = hash(val);
    HashNode* curr = obj->buckets[h];
    bool notPresent = true;
    
    // Check if it already exists (just to return the correct boolean)
    while (curr != NULL) {
        if (curr->key == val) {
            notPresent = false;
            break;
        }
        curr = curr->next;
    }
    
    // 1. Add to array
    obj->nums[obj->size] = val;
    
    // 2. Prepend a new node to the Hash Map bucket (Duplicates get their own nodes!)
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->key = val;
    newNode->arr_idx = obj->size;
    newNode->next = obj->buckets[h];
    obj->buckets[h] = newNode;
    
    obj->size++;
    return notPresent;
}

bool randomizedCollectionRemove(RandomizedCollection* obj, int val) {
    int h = hash(val);
    HashNode* curr = obj->buckets[h];
    HashNode* prev = NULL;
    
    // Find ANY node matching the target value
    while (curr != NULL && curr->key != val) {
        prev = curr;
        curr = curr->next;
    }
    
    if (curr == NULL) return false; // Not found
    
    int idxToRemove = curr->arr_idx;
    int lastIdx = obj->size - 1;
    int lastVal = obj->nums[lastIdx];
    
    // Remove target node from the hash map linked list
    if (prev == NULL) {
        obj->buckets[h] = curr->next;
    } else {
        prev->next = curr->next;
    }
    free(curr); // Free the specific node
    
    // Overwrite target in array with last value
    obj->nums[idxToRemove] = lastVal;
    
    // If we didn't just delete the last element naturally, update lastVal's node
    if (idxToRemove != lastIdx) {
        int lastH = hash(lastVal);
        HashNode* updateNode = obj->buckets[lastH];
        
        // We must find the specific node for lastVal that was pointing to the tail!
        while (updateNode != NULL) {
            if (updateNode->key == lastVal && updateNode->arr_idx == lastIdx) {
                updateNode->arr_idx = idxToRemove;
                break;
            }
            updateNode = updateNode->next;
        }
    }
    
    obj->size--;
    return true;
}

int randomizedCollectionGetRandom(RandomizedCollection* obj) {
    return obj->nums[rand() % obj->size];
}

void randomizedCollectionFree(RandomizedCollection* obj) {
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