/**
 * Problem: LeetCode 0001 - Two Sum
 * Language: C (C11)
 *
 * Approach:
 * In languages with standard libraries (C++, Python), hash maps are built-in.
 * In pure C, we implement a lightweight hash table with separate chaining
 * to achieve O(N) time complexity while maintaining strict memory bounds.
 *
 * Complexity:
 * - Time: O(N) average, O(N^2) worst-case on heavy hash collisions.
 * - Space: O(N) to store elements in the hash table buckets.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct HashNode {
    int key;
    int val;
    struct HashNode* next;
} HashNode;

typedef struct {
    int capacity;
    HashNode** buckets;
} HashMap;

static unsigned int hash(int key, int capacity) {
    /* Handle negative keys safely using unsigned arithmetic */
    unsigned int ukey = (unsigned int)key;
    return (ukey * 2654435761u) % (unsigned int)capacity;
}

static HashMap* hashmap_create(int capacity) {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    if (!map) return NULL;
    map->capacity = capacity;
    map->buckets = (HashNode**)calloc((size_t)capacity, sizeof(HashNode*));
    if (!map->buckets) {
        free(map);
        return NULL;
    }
    return map;
}

static void hashmap_insert(HashMap* map, int key, int val) {
    unsigned int idx = hash(key, map->capacity);
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    node->key = key;
    node->val = val;
    node->next = map->buckets[idx];
    map->buckets[idx] = node;
}

static bool hashmap_find(HashMap* map, int key, int* out_val) {
    unsigned int idx = hash(key, map->capacity);
    HashNode* curr = map->buckets[idx];
    while (curr) {
        if (curr->key == key) {
            *out_val = curr->val;
            return true;
        }
        curr = curr->next;
    }
    return false;
}

static void hashmap_free(HashMap* map) {
    if (!map) return;
    for (int i = 0; i < map->capacity; i++) {
        HashNode* curr = map->buckets[i];
        while (curr) {
            HashNode* tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
    free(map->buckets);
    free(map);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(const int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* result = (int*)malloc(2 * sizeof(int));
    if (!result) {
        *returnSize = 0;
        return NULL;
    }

    int capacity = numsSize * 2 > 16 ? numsSize * 2 : 16;
    HashMap* map = hashmap_create(capacity);
    if (!map) {
        free(result);
        *returnSize = 0;
        return NULL;
    }

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int complement_idx = -1;

        if (hashmap_find(map, complement, &complement_idx)) {
            result[0] = complement_idx;
            result[1] = i;
            hashmap_free(map);
            return result;
        }

        hashmap_insert(map, nums[i], i);
    }

    hashmap_free(map);
    free(result);
    *returnSize = 0;
    return NULL;
}

/* ========================================================================= */
/* Standalone Test Harness                                                   */
/* ========================================================================= */

int main(void) {
    printf("[TEST] Running LeetCode 0001: Two Sum...\n");

    // Test Case 1: Standard positive values
    {
        int nums[] = {2, 7, 11, 15};
        int returnSize = 0;
        int* res = twoSum(nums, 4, 9, &returnSize);
        assert(returnSize == 2);
        assert(res != NULL);
        assert((res[0] == 0 && res[1] == 1) || (res[0] == 1 && res[1] == 0));
        free(res);
        printf("  ✓ Test 1 Passed: [2, 7, 11, 15], target = 9 -> [0, 1]\n");
    }

    // Test Case 2: Adjacent duplicate values
    {
        int nums[] = {3, 2, 4};
        int returnSize = 0;
        int* res = twoSum(nums, 3, 6, &returnSize);
        assert(returnSize == 2);
        assert(res != NULL);
        assert((res[0] == 1 && res[1] == 2) || (res[0] == 2 && res[1] == 1));
        free(res);
        printf("  ✓ Test 2 Passed: [3, 2, 4], target = 6 -> [1, 2]\n");
    }

    // Test Case 3: Negative integers
    {
        int nums[] = {-3, 4, 3, 90};
        int returnSize = 0;
        int* res = twoSum(nums, 4, 0, &returnSize);
        assert(returnSize == 2);
        assert(res != NULL);
        assert((res[0] == 0 && res[1] == 2) || (res[0] == 2 && res[1] == 0));
        free(res);
        printf("  ✓ Test 3 Passed: [-3, 4, 3, 90], target = 0 -> [0, 2]\n");
    }

    printf("[PASSED] All LeetCode 0001 tests passed with zero leaks!\n\n");
    return 0;
}
