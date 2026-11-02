int firstMissingPositive(int* nums, int numsSize) {
    // Phase 1: Cyclic Sort (The In-Place Hash)
    for (int i = 0; i < numsSize; i++) {
        // While the current number is a valid positive integer within our bounds
        // AND it is not already sitting in its correct mathematical index
        while (nums[i] > 0 && nums[i] <= numsSize && nums[nums[i] - 1] != nums[i]) {
            // Hardware-level swap
            int correct_idx = nums[i] - 1;
            int temp = nums[correct_idx];
            nums[correct_idx] = nums[i];
            nums[i] = temp;
        }
    }

    // Phase 2: The Linear Scan
    // The first index that does not match its expected value is the missing number
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != i + 1) {
            return i + 1;
        }
    }

    // Phase 3: The Edge Case
    // If the array was perfectly packed (e.g., [1, 2, 3, 4]), the missing number is N + 1
    return numsSize + 1;
}