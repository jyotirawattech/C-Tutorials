int search(int* nums, int numsSize, int target) {
    int left = 0;
    int right = numsSize - 1;
    
    while (left <= right) {
        // HARDWARE FIX: Safe midpoint calculation
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            return mid;
        }
        
        // State Machine Branch 1: The Left Half is perfectly sorted
        if (nums[left] <= nums[mid]) {
            // Is the target mathematically bounded within this sorted anchor?
            if (nums[left] <= target && target < nums[mid]) {
                right = mid - 1; // Discard right half
            } else {
                left = mid + 1;  // Discard left half
            }
        } 
        // State Machine Branch 2: The Right Half MUST be perfectly sorted
        else {
            // Is the target mathematically bounded within this sorted anchor?
            if (nums[mid] < target && target <= nums[right]) {
                left = mid + 1;  // Discard left half
            } else {
                right = mid - 1; // Discard right half
            }
        }
    }
    
    return -1; // Target not found in the ring buffer
}