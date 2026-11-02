/**
 * Problem: LeetCode 0704 - Binary Search
 * Language: C (C11)
 *
 * Approach:
 * Classic iterative binary search. Avoids the famous 32-bit integer overflow bug
 * by calculating midpoint as `low + (high - low) / 2` instead of `(low + high) / 2`.
 *
 * Complexity:
 * - Time: O(log N) logarithmic search over sorted contiguous memory.
 * - Space: O(1) in-place stack memory.
 */

#include <stdio.h>
#include <assert.h>

int search(const int* nums, int numsSize, int target) {
    if (!nums || numsSize <= 0) return -1;

    int low = 0;
    int high = numsSize - 1;

    while (low <= high) {
        // Prevents (low + high) integer overflow when sum exceeds INT_MAX
        int mid = low + (high - low) / 2;

        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

/* ========================================================================= */
/* Standalone Test Harness                                                   */
/* ========================================================================= */

int main(void) {
    printf("[TEST] Running LeetCode 0704: Binary Search...\n");

    // Test Case 1: Target found in middle [-1, 0, 3, 5, 9, 12], target = 9 -> index 4
    {
        int nums[] = {-1, 0, 3, 5, 9, 12};
        int res = search(nums, 6, 9);
        assert(res == 4);
        printf("  ✓ Test 1 Passed: search(nums, 6, 9) -> index 4\n");
    }

    // Test Case 2: Target absent [-1, 0, 3, 5, 9, 12], target = 2 -> -1
    {
        int nums[] = {-1, 0, 3, 5, 9, 12};
        int res = search(nums, 6, 2);
        assert(res == -1);
        printf("  ✓ Test 2 Passed: search(nums, 6, 2) -> -1\n");
    }

    // Test Case 3: Single element matching [5], target = 5 -> index 0
    {
        int nums[] = {5};
        int res = search(nums, 1, 5);
        assert(res == 0);
        printf("  ✓ Test 3 Passed: search([5], 1, 5) -> index 0\n");
    }

    // Test Case 4: Single element missing [5], target = -5 -> -1
    {
        int nums[] = {5};
        int res = search(nums, 1, -5);
        assert(res == -1);
        printf("  ✓ Test 4 Passed: search([5], 1, -5) -> -1\n");
    }

    printf("[PASSED] All LeetCode 0704 tests passed with zero leaks!\n\n");
    return 0;
}
