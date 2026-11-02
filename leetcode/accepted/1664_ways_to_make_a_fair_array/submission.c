int waysToMakeFair(int* nums, int numsSize) {
    long long right_even = 0;
    long long right_odd = 0;
    long long left_even = 0;
    long long left_odd = 0;
    
    // Phase 1: Initialize the right side accumulators
    for (int i = 0; i < numsSize; i++) {
        if (i % 2 == 0) {
            right_even += nums[i];
        } else {
            right_odd += nums[i];
        }
    }
    
    int valid_count = 0;
    
    // Phase 2: Stream through the array, testing removal at each index
    for (int i = 0; i < numsSize; i++) {
        // Step A: Temporarily remove the current element from the right side
        if (i % 2 == 0) {
            right_even -= nums[i];
        } else {
            right_odd -= nums[i];
        }
        
        // Step B: Check the Parity Swap Condition
        // If we remove index i, the right side's evens become odds, and odds become evens.
        long long new_even_sum = left_even + right_odd;
        long long new_odd_sum = left_odd + right_even;
        
        if (new_even_sum == new_odd_sum) {
            valid_count++;
        }
        
        // Step C: Permanently add the current element to the left side
        if (i % 2 == 0) {
            left_even += nums[i];
        } else {
            left_odd += nums[i];
        }
    }
    
    return valid_count;
}