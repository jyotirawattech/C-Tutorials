#include <stdlib.h>

// Standard safe comparator for qsort
int compare(const void* a, const void* b) {
    int int_a = *(const int*)a;
    int int_b = *(const int*)b;
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

int reductionOperations(int* nums, int numsSize) {
    // 1. Sort the array to group identical states and build ascending tiers
    qsort(nums, numsSize, sizeof(int), compare);
    
    int current_tier_cost = 0;
    int total_operations = 0; // The problem constraints allow this to fit in a 32-bit int, 
                              // but in production, make this a long long!
    
    // 2. Stream through the memory sequentially
    for (int i = 1; i < numsSize; i++) {
        // If we step up to a new, larger number, the cost to reduce it to the base increases by 1
        if (nums[i] > nums[i - 1]) {
            current_tier_cost++;
        }
        
        // Accumulate the cost for the current element
        total_operations += current_tier_cost;
    }
    
    return total_operations;
}