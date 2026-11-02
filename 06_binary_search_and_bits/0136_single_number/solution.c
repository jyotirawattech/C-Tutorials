/**
 * Problem: LeetCode 0136 - Single Number
 * Language: C (C11)
 *
 * Approach:
 * Bitwise XOR operation.
 * Utilizes fundamental boolean algebra properties:
 *   - A ^ A = 0 (self-inverse)
 *   - A ^ 0 = A (identity)
 *   - Commutative and associative: order of elements does not matter.
 *
 * All paired numbers cancel to 0; only the single unique integer survives.
 *
 * Complexity:
 * - Time: O(N) single-pass linear streaming over memory.
 * - Space: O(1) single register accumulator, zero dynamic memory.
 */

#include <stdio.h>
#include <assert.h>

int singleNumber(const int* nums, int numsSize) {
    int unique = 0;
    for (int i = 0; i < numsSize; i++) {
        unique ^= nums[i];
    }
    return unique;
}

/* ========================================================================= */
/* Standalone Test Harness                                                   */
/* ========================================================================= */

int main(void) {
    printf("[TEST] Running LeetCode 0136: Single Number...\n");

    // Test Case 1: [2, 2, 1] -> 1
    {
        int nums[] = {2, 2, 1};
        int res = singleNumber(nums, 3);
        assert(res == 1);
        printf("  ✓ Test 1 Passed: [2, 2, 1] -> 1\n");
    }

    // Test Case 2: [4, 1, 2, 1, 2] -> 4
    {
        int nums[] = {4, 1, 2, 1, 2};
        int res = singleNumber(nums, 5);
        assert(res == 4);
        printf("  ✓ Test 2 Passed: [4, 1, 2, 1, 2] -> 4\n");
    }

    // Test Case 3: Single element [1] -> 1
    {
        int nums[] = {1};
        int res = singleNumber(nums, 1);
        assert(res == 1);
        printf("  ✓ Test 3 Passed: [1] -> 1\n");
    }

    // Test Case 4: Negative numbers [-2, -2, -5] -> -5
    {
        int nums[] = {-2, -2, -5};
        int res = singleNumber(nums, 3);
        assert(res == -5);
        printf("  ✓ Test 4 Passed: [-2, -2, -5] -> -5\n");
    }

    printf("[PASSED] All LeetCode 0136 tests passed with zero leaks!\n\n");
    return 0;
}
