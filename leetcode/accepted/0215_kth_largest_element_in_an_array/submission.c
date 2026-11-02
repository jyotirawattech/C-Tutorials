#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// The Divide and Conquer Recursion with 3-Way Partitioning
void quickselect_3way(int* nums, int left, int right, int target_index) {
    if (left >= right) return;
    
    // HARDWARE FIX: Random pivot selection
    int pivotIndex = left + rand() % (right - left + 1);
    int pivotValue = nums[pivotIndex];
    
    // Set up our 3 boundary pointers
    int curr = left;      // The scout pointer reading the array
    int lt = left;        // The boundary for elements < pivot
    int gt = right;       // The boundary for elements > pivot
    
    // Sweep the active memory block
    while (curr <= gt) {
        if (nums[curr] < pivotValue) {
            // Found a smaller element, swap it to the left boundary
            swap(&nums[curr], &nums[lt]);
            curr++;
            lt++;
        } else if (nums[curr] > pivotValue) {
            // Found a larger element, swap it to the right boundary
            // We do NOT increment curr here because the new element swapped 
            // into curr from the right needs to be evaluated next!
            swap(&nums[curr], &nums[gt]);
            gt--;
        } else {
            // Element equals the pivot. Just absorb it into the middle block!
            curr++;
        }
    }
    
    // After the loop, the array is perfectly divided:
    // [left to lt-1] are < pivot
    // [lt to gt] are EXACTLY == pivot
    // [gt+1 to right] are > pivot
    
    // Decide which path to take
    if (target_index >= lt && target_index <= gt) {
        // The target index falls inside the massive block of identical pivots. We win!
        return; 
    } else if (target_index < lt) {
        // Target is in the smaller sector
        quickselect_3way(nums, left, lt - 1, target_index);
    } else {
        // Target is in the larger sector
        quickselect_3way(nums, gt + 1, right, target_index);
    }
}

int findKthLargest(int* nums, int numsSize, int k) {
    // Seed the random number generator
    srand(time(NULL));
    
    // Calculate the target index
    int target_index = numsSize - k;
    
    // Execute the hardened state machine
    quickselect_3way(nums, 0, numsSize - 1, target_index);
    
    // The target index now mathematically holds the correct element
    return nums[target_index];
}