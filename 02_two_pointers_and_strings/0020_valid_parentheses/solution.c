/**
 * Problem: LeetCode 0020 - Valid Parentheses
 * Language: C (C11)
 *
 * Approach:
 * Implements a bounded LIFO stack in pure C. For a string of length N,
 * the maximum stack depth is N. We allocate stack memory dynamically,
 * push matching closing brackets, and verify match on pop.
 *
 * Complexity:
 * - Time: O(N) single-pass scan.
 * - Space: O(N) bounded heap/stack buffer with zero leaks.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

bool isValid(const char* s) {
    if (!s) return false;
    size_t len = strlen(s);
    if (len % 2 != 0) return false; // Odd length can never be balanced

    char* stack = (char*)malloc(len);
    if (!stack) return false;

    int top = -1;

    for (size_t i = 0; i < len; i++) {
        char c = s[i];
        if (c == '(') {
            stack[++top] = ')';
        } else if (c == '{') {
            stack[++top] = '}';
        } else if (c == '[') {
            stack[++top] = ']';
        } else {
            // Closing bracket encountered
            if (top == -1 || stack[top] != c) {
                free(stack);
                return false;
            }
            top--;
        }
    }

    bool balanced = (top == -1);
    free(stack);
    return balanced;
}

/* ========================================================================= */
/* Standalone Test Harness                                                   */
/* ========================================================================= */

int main(void) {
    printf("[TEST] Running LeetCode 0020: Valid Parentheses...\n");

    // Test Case 1: Simple pair "()"
    assert(isValid("()") == true);
    printf("  ✓ Test 1 Passed: \"()\" -> valid\n");

    // Test Case 2: Multi brackets "()[]{}"
    assert(isValid("()[]{}") == true);
    printf("  ✓ Test 2 Passed: \"()[]{}\" -> valid\n");

    // Test Case 3: Mismatched brackets "(]"
    assert(isValid("(]") == false);
    printf("  ✓ Test 3 Passed: \"(]\" -> invalid\n");

    // Test Case 4: Nested brackets "([{}])"
    assert(isValid("([{}])") == true);
    printf("  ✓ Test 4 Passed: \"([{}])\" -> valid\n");

    // Test Case 5: Incomplete opening "["
    assert(isValid("[") == false);
    printf("  ✓ Test 5 Passed: \"[\" -> invalid\n");

    printf("[PASSED] All LeetCode 0020 tests passed with zero leaks!\n\n");
    return 0;
}
