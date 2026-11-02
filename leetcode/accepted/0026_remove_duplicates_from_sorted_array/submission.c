int removeDuplicates(int* nums, int numsSize) {
    // If the array is empty, there are 0 unique elements
    if (numsSize == 0) return 0;
    
    // 'slow' points to the index of the last unique element we have confirmed
    int slow = 0;
    
    // 'fast' scans through the array to find new unique elements
    for (int fast = 1; fast < numsSize; fast++) {
        // If the element at 'fast' is different from the last unique element
        if (nums[fast] != nums[slow]) {
            // Move the slow pointer forward
            slow++;
            // Update the new position with the unique element found
            nums[slow] = nums[fast];
        }
    }
    
    // The number of unique elements is the index of the last unique element + 1
    return slow + 1;
}