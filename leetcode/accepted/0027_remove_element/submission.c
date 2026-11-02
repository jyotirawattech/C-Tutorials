int removeElement(int* nums, int numsSize, int val) {
    int slow = 0;
    
    for (int fast = 0; fast < numsSize; fast++) {
        // If the current element is not the one we want to remove
        if (nums[fast] != val) {
            // Place it at the 'slow' position and advance
            nums[slow] = nums[fast];
            slow++;
        }
    }
    
    // 'slow' is now exactly the count of valid elements (k)
    return slow;
}