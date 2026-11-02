#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getConcatenation(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize * 2;
    int* ans = (int*)malloc(sizeof(int) * (*returnSize));
    
    for (int i = 0; i < numsSize; i++) {
        ans[i] = nums[i];           // Fill first half
        ans[i + numsSize] = nums[i]; // Fill second half
    }
    
    return ans;
}