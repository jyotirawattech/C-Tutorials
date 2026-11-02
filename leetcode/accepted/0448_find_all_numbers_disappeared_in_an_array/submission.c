#include <stdlib.h>
#include <math.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize) {
    // Pass 1: Sign Flipping
    for (int i = 0; i < numsSize; i++) {
        int target_idx = abs(nums[i]) - 1;
        
        if (nums[target_idx] > 0) {
            nums[target_idx] = -nums[target_idx];
        }
    }
    
    // Allocate max possible memory (1 malloc is faster than reallocating)
    int* missing_nums = (int*)malloc(numsSize * sizeof(int));
    int count = 0;
    
    // Pass 2: Extract positives
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > 0) {
            missing_nums[count++] = i + 1;
        }
    }
    
    *returnSize = count;
    return missing_nums;
}