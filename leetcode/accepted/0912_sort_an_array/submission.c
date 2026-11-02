// Iterative, hardware-safe swap
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Iterative Sift-Down (O(1) Space, zero Call Stack overhead)
void siftDown(int* nums, int n, int i) {
    int largest;
    
    while (1) {
        largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // Check if left child exists and is greater than root
        if (left < n && nums[left] > nums[largest]) {
            largest = left;
        }

        // Check if right child exists and is greater than the largest so far
        if (right < n && nums[right] > nums[largest]) {
            largest = right;
        }

        // If the largest is not the root, swap and continue sifting down
        if (largest != i) {
            swap(&nums[i], &nums[largest]);
            i = largest; // Move the pointer down the tree
        } else {
            // The heap property is satisfied, break the loop
            break;
        }
    }
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize; // Required by LeetCode C signature
    
    // Phase 1: Build the Max-Heap
    // We start from the last non-leaf node and sift down to the root
    for (int i = numsSize / 2 - 1; i >= 0; i--) {
        siftDown(nums, numsSize, i);
    }

    // Phase 2: Extract elements one by one from the heap
    for (int i = numsSize - 1; i > 0; i--) {
        // Move current maximum (at root index 0) to the end of the active array
        swap(&nums[0], &nums[i]);
        
        // Sift down the new root on the reduced heap size
        siftDown(nums, i, 0);
    }

    return nums;
}