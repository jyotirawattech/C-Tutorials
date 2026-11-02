int peakIndexInMountainArray(int* arr, int arrSize) {
    int left = 0;
    int right = arrSize - 1;
    
    // We loop until the left and right pointers collide at the peak
    while (left < right) {
        // HARDWARE FIX: Prevent 32-bit integer overflow during mid calculation
        int mid = left + (right - left) / 2;
        
        // Evaluate the trajectory (slope)
        if (arr[mid] < arr[mid + 1]) {
            // We are ascending. The peak is definitively to the right.
            // Because arr[mid] is strictly less than arr[mid+1], 
            // arr[mid] cannot possibly be the peak. We skip it entirely.
            left = mid + 1;
        } else {
            // We are descending (or currently on the peak).
            // The peak is to the left, but arr[mid] MIGHT be the peak itself.
            // Therefore, we cannot do mid - 1. We must keep mid.
            right = mid;
        }
    }
    
    // When left == right, we have collapsed the search space to a single index
    return left;
}