#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* smallerNumbersThanCurrent(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* ans = (int*)malloc(numsSize * sizeof(int));
    
    // Constraint: 0 <= nums[i] <= 100
    int count[101] = {0};
    
    // 1. Calculate Frequencies
    for (int i = 0; i < numsSize; i++) {
        count[nums[i]]++;
    }
    
    // 2. Transform into Prefix Sums (strictly smaller)
    int running_sum = 0;
    for (int i = 0; i <= 100; i++) {
        int current_freq = count[i];
        count[i] = running_sum;
        running_sum += current_freq;
    }
    
    // 3. Instant Lookup
    for (int i = 0; i < numsSize; i++) {
        ans[i] = count[nums[i]];
    }
    
    return ans;
}