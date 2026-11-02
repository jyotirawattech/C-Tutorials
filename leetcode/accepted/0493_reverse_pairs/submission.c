#include <stdlib.h>

// The Recursive Divide & Conquer Engine
int merge_sort_and_count(int* nums, int* temp, int left, int right) {
    // Base Case: An array of 0 or 1 elements has 0 pairs
    if (left >= right) {
        return 0;
    }
    
    // HARDWARE FIX: Safe midpoint calculation to prevent index overflow
    int mid = left + (right - left) / 2;
    
    // 1. Recurse down to the bottom of the Call Stack
    int count = merge_sort_and_count(nums, temp, left, mid) + 
                merge_sort_and_count(nums, temp, mid + 1, right);
                
    // 2. Cross-Boundary Counting (The Core Logic)
    // Both [left to mid] and [mid+1 to right] are currently sorted.
    int j = mid + 1;
    for (int i = left; i <= mid; i++) {
        // HARDWARE FIX: Cast to 64-bit long long to prevent 2 * nums[j] from overflowing
        while (j <= right && (long long)nums[i] > 2LL * (long long)nums[j]) {
            j++;
        }
        // If nums[i] > 2*nums[j-1], then it is greater than all right-half elements up to j-1
        count += (j - (mid + 1));
    }
    
    // 3. Standard Merge Step (In-Place sorting via temporary buffer)
    int i = left;
    j = mid + 1;
    int k = left; // Index for our temp array
    
    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j]) {
            temp[k++] = nums[i++];
        } else {
            temp[k++] = nums[j++];
        }
    }
    
    // Drain any remaining elements
    while (i <= mid) {
        temp[k++] = nums[i++];
    }
    while (j <= right) {
        temp[k++] = nums[j++];
    }
    
    // 4. Commit the sorted memory block back to the main array
    for (int p = left; p <= right; p++) {
        nums[p] = temp[p];
    }
    
    return count;
}

int reversePairs(int* nums, int numsSize) {
    if (numsSize <= 1) return 0;
    
    // ARCHITECTURAL OPTIMIZATION: Single Memory Allocation
    // Instead of allocating memory inside every recursive frame (which causes
    // massive heap fragmentation and latency), we allocate one single 
    // O(N) temporary buffer at the very top and pass the pointer down.
    int* temp = (int*)malloc(numsSize * sizeof(int));
    if (!temp) return 0; // Hardware safety check
    
    int total_reverse_pairs = merge_sort_and_count(nums, temp, 0, numsSize - 1);
    
    // Clean up our singular heap allocation
    free(temp);
    
    return total_reverse_pairs;
}