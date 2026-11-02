#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* shuffle(int* nums, int numsSize, int n, int* returnSize) {
    *returnSize = numsSize;
    int* ans = (int*)malloc(numsSize * sizeof(int));
    
    // Set up dedicated pointers
    int* x_ptr = nums;         // Points to start of X half
    int* y_ptr = nums + n;     // Points to start of Y half
    int* write_ptr = ans;      // Points to start of destination
    
    // Unrolled, branchless pointer writing
    for (int i = 0; i < n; i++) {
        *write_ptr++ = *x_ptr++;  // Write X, increment both
        *write_ptr++ = *y_ptr++;  // Write Y, increment both
    }
    
    return ans;
}