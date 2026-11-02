int removeDuplicates(int* nums, int numsSize) {
    // If the array has 2 or fewer elements, it's already valid.
    if (numsSize <= 2) {
        return numsSize;
    }
    
    // 'slow' points to the index where the next valid element should go.
    // We start at 2 because the first two elements are always kept.
    int slow = 2;
    
    // 'fast' scans through the array starting from the 3rd element.
    for (int fast = 2; fast < numsSize; fast++) {
        // We only accept the element if it's different from the element 
        // sitting two positions behind our insertion point.
        if (nums[fast] != nums[slow - 2]) {
            nums[slow] = nums[fast];
            slow++;
        }
    }
    
    // 'slow' naturally tracks the new length of the compacted array.
    return slow;
}