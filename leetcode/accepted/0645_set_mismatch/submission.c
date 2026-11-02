#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findErrorNums(int* nums, int numsSize, int* returnSize) {
    int xor_all = 0;
    
    // 1. XOR all array elements and all numbers from 1 to N
    for (int i = 0; i < numsSize; i++) {
        xor_all ^= nums[i];
        xor_all ^= (i + 1);
    }
    // xor_all now exactly equals (Duplicate ^ Missing)
    
    // 2. Find the rightmost set bit (the distinguishing bit)
    // We cast to unsigned int to safely negate in C without undefined behavior on INT_MIN
    int rightmost_set_bit = xor_all & -(unsigned int)xor_all;
    
    int bucketX = 0, bucketY = 0;
    
    // 3. Partition everything into two buckets based on that bit
    for (int i = 0; i < numsSize; i++) {
        // Partition the array elements
        if (nums[i] & rightmost_set_bit) bucketX ^= nums[i];
        else bucketY ^= nums[i];
        
        // Partition the expected numbers 1 to N
        if ((i + 1) & rightmost_set_bit) bucketX ^= (i + 1);
        else bucketY ^= (i + 1);
    }
    
    // 4. We now have our two numbers, but which is the duplicate?
    int* res = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;
    
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == bucketX) {
            res[0] = bucketX; // Found bucketX in the array, so it's the duplicate
            res[1] = bucketY;
            return res;
        }
    }
    
    // Otherwise, bucketY is the duplicate
    res[0] = bucketY;
    res[1] = bucketX;
    return res;
}