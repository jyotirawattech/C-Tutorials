#include <stdio.h>

int findMaxConsecutiveOnes(int* nums, int numsSize) {
    int max_count = 0;
    int current_count = 0;
    
    for (int i = 0; i < numsSize; i++) {
        // Branchless Reset: If nums[i] is 0, this multiplies by 0. 
        // If nums[i] is 1, it adds 1 and multiplies by 1.
        current_count = (current_count + nums[i]) * nums[i];
        
        // We still use an if here for the max check, but the frequent 
        // 0/1 state reset is entirely branchless.
        if (current_count > max_count) {
            max_count = current_count;
        }
    }
    
    return max_count;
}