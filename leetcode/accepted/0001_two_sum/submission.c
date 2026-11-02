#include <stdlib.h>
#include <math.h>

// 1. Define the Hash Node for Separate Chaining (Collision Resolution)
typedef struct HashNode {
    int key;       // The number from the array
    int value;     // The original index of the number
    struct HashNode* next;
} HashNode;

// Fast hashing function handling negative integers
int getHash(int key, int size) {
    int hash = key % size;
    return hash < 0 ? hash + size : hash;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* result = (int*)malloc(2 * sizeof(int));
    
    // 2. Allocate the Hash Table Array
    // A prime number larger than the max constraints helps prevent collisions
    int tableSize = 10007; 
    HashNode** hashTable = (HashNode**)calloc(tableSize, sizeof(HashNode*));
    
    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int compHash = getHash(complement, tableSize);
        
        // 3. Search for the complement in the Hash Table
        HashNode* curr = hashTable[compHash];
        while (curr != NULL) {
            if (curr->key == complement) {
                result[0] = curr->value;
                result[1] = i;
                
                // 4. HARDWARE FIX: Prevent memory leak by freeing the table before returning
                for (int j = 0; j < tableSize; j++) {
                    HashNode* temp = hashTable[j];
                    while (temp != NULL) {
                        HashNode* toFree = temp;
                        temp = temp->next;
                        free(toFree);
                    }
                }
                free(hashTable);
                return result;
            }
            curr = curr->next;
        }
        
        // 5. If complement not found, insert current number into Hash Table
        int numHash = getHash(nums[i], tableSize);
        HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
        newNode->key = nums[i];
        newNode->value = i;
        // Insert at head of the linked list (chain) for this bucket
        newNode->next = hashTable[numHash]; 
        hashTable[numHash] = newNode;
    }
    
    // Fallback if no solution is found (though constraints guarantee one)
    free(hashTable);
    return result;
}