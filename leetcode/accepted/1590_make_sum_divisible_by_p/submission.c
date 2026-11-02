#include <stdlib.h>

// 1. Custom Hash Map Node for O(1) lookups
typedef struct HashNode {
    int key;       // The prefix modulo
    int value;     // The most recent index
    struct HashNode* next;
} HashNode;

int getHash(int key, int size) {
    return key % size;
}

int minSubarray(int* nums, int numsSize, int p) {
    // HARDWARE FIX: Prevent 32-bit Integer Overflow
    long long totalSum = 0;
    for (int i = 0; i < numsSize; i++) {
        totalSum += nums[i];
    }
    
    int target = totalSum % p;
    if (target == 0) return 0; // Already aligned
    
    // Allocate Hash Table
    int tableSize = 100003; // Prime number > N
    HashNode** hashMap = (HashNode**)calloc(tableSize, sizeof(HashNode*));
    
    // Insert Base Case: {0: -1}
    HashNode* baseNode = (HashNode*)malloc(sizeof(HashNode));
    baseNode->key = 0;
    baseNode->value = -1;
    baseNode->next = NULL;
    hashMap[0] = baseNode;
    
    long long currentPrefix = 0;
    int minLength = numsSize;
    
    for (int i = 0; i < numsSize; i++) {
        currentPrefix = (currentPrefix + nums[i]) % p;
        
        // Calculate the mathematical complement needed to fix the alignment
        int needed = (currentPrefix - target + p) % p;
        
        // Hash Map Lookup
        int hashIdx = getHash(needed, tableSize);
        HashNode* curr = hashMap[hashIdx];
        while (curr != NULL) {
            if (curr->key == needed) {
                int length = i - curr->value;
                if (length < minLength) {
                    minLength = length;
                }
                break; // Found the most recent (largest index)
            }
            curr = curr->next;
        }
        
        // Hash Map Insert/Update Current Prefix
        int currHash = getHash(currentPrefix, tableSize);
        curr = hashMap[currHash];
        int updated = 0;
        while (curr != NULL) {
            if (curr->key == currentPrefix) {
                curr->value = i; // Update to the most recent index
                updated = 1;
                break;
            }
            curr = curr->next;
        }
        if (!updated) {
            HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
            newNode->key = currentPrefix;
            newNode->value = i;
            newNode->next = hashMap[currHash];
            hashMap[currHash] = newNode;
        }
    }
    
    // Free Memory (crucial for systems engineering)
    for (int i = 0; i < tableSize; i++) {
        HashNode* curr = hashMap[i];
        while (curr != NULL) {
            HashNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(hashMap);
    
    return minLength == numsSize ? -1 : minLength;
}