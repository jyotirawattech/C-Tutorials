long long countMajoritySubarrays(int* nums, int numsSize, int target) {
    // 1. The Hash Map Bounding
    // The maximum possible prefix sum is +numsSize, and the minimum is -numsSize.
    // We offset by +numsSize to safely map negative sums to positive array indices.
    int offset = numsSize + 1;
    int mapSize = 2 * numsSize + 3;
    
    // Thread-safe heap allocation of our zero-initialized state tracker (~800 KB)
    int* count = (int*)calloc(mapSize, sizeof(int));
    if (!count) return 0; // Hardware safety check
    
    // Base case: Before processing any numbers, we have seen a sum of 0 exactly once
    count[offset] = 1;
    
    int curr_sum = 0;
    
    // HARDWARE FIX: Prevent 32-bit Integer Overflow. Max pairs can reach 5 Billion!
    long long valid_past_sums = 0;
    long long total_valid_subarrays = 0;
    
    // 2. The O(N) Sliding Validity Machine
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == target) {
            // The sum is going UP (+1)
            // The previous sum we were standing on is now strictly smaller than us.
            // We instantly absorb all its occurrences into our valid pool.
            valid_past_sums += count[curr_sum + offset];
            curr_sum++;
        } else {
            // The sum is going DOWN (-1)
            // We are stepping down onto a new sum. Any past occurrences of this 
            // new sum are exactly equal to us, meaning they are NO LONGER strictly smaller.
            // We instantly eject them from our valid pool.
            curr_sum--;
            valid_past_sums -= count[curr_sum + offset];
        }
        
        // 3. Accumulate mathematically proven pairs
        total_valid_subarrays += valid_past_sums;
        
        // 4. Record the current state into our map
        count[curr_sum + offset]++;
    }
    
    // Return memory to the OS
    free(count);
    
    return total_valid_subarrays;
}