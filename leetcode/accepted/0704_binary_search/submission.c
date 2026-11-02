int search(int* nums, int numsSize, int target) {
    int left = 0;
    int right = numsSize - 1;
    
    // We use <= because the target might be at the exact index 
    // where left and right finally collide.
    while (left <= right) {
        // HARDWARE FIX: Prevent 32-bit Integer Overflow
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            return mid; // Target acquired
        } else if (nums[mid] < target) {
            // The midpoint is too small. The target must be in the right half.
            left = mid + 1;
        } else {
            // The midpoint is too large. The target must be in the left half.
            right = mid - 1;
        }
    }
    
    // If the loop exits, left has crossed right, meaning the target does not exist.
    return -1;
}