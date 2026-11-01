/**
 * Problem: LeetCode 0003 - Longest Substring Without Repeating Characters
 * Language: C (C11)
 *
 * Approach:
 * Sliding window using direct-indexed ASCII table of 256 entries.
 * Avoids any dynamic heap allocations entirely (zero malloc), which is
 * standard best practice in embedded and systems environments.
 *
 * Complexity:
 * - Time: O(N) where N is the length of string s (single pass).
 * - Space: O(1) constant auxiliary space (256-int table allocated on stack).
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

int lengthOfLongestSubstring(const char* s) {
    if (!s) return 0;

    int last_index[256];
    for (int i = 0; i < 256; i++) {
        last_index[i] = -1;
    }

    int max_len = 0;
    int window_start = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        unsigned char c = (unsigned char)s[i];

        // If the character was seen inside the current sliding window, move window_start
        if (last_index[c] >= window_start) {
            window_start = last_index[c] + 1;
        }

        last_index[c] = i;
        int current_len = i - window_start + 1;
        if (current_len > max_len) {
            max_len = current_len;
        }
    }

    return max_len;
}

/* ========================================================================= */
/* Standalone Test Harness                                                   */
/* ========================================================================= */

int main(void) {
    printf("[TEST] Running LeetCode 0003: Longest Substring Without Repeating Characters...\n");

    // Test Case 1: Standard repeating chars
    {
        const char* s = "abcabcbb";
        int res = lengthOfLongestSubstring(s);
        assert(res == 3);
        printf("  ✓ Test 1 Passed: \"%s\" -> %d (expected 3: \"abc\")\n", s, res);
    }

    // Test Case 2: All same chars
    {
        const char* s = "bbbbb";
        int res = lengthOfLongestSubstring(s);
        assert(res == 1);
        printf("  ✓ Test 2 Passed: \"%s\" -> %d (expected 1: \"b\")\n", s, res);
    }

    // Test Case 3: Substring with gap
    {
        const char* s = "pwwkew";
        int res = lengthOfLongestSubstring(s);
        assert(res == 3);
        printf("  ✓ Test 3 Passed: \"%s\" -> %d (expected 3: \"wke\")\n", s, res);
    }

    // Test Case 4: Empty string
    {
        const char* s = "";
        int res = lengthOfLongestSubstring(s);
        assert(res == 0);
        printf("  ✓ Test 4 Passed: \"%s\" -> %d (expected 0)\n", s, res);
    }

    // Test Case 5: Single character
    {
        const char* s = " ";
        int res = lengthOfLongestSubstring(s);
        assert(res == 1);
        printf("  ✓ Test 5 Passed: \"%s\" -> %d (expected 1)\n", s, res);
    }

    printf("[PASSED] All LeetCode 0003 tests passed with zero leaks!\n\n");
    return 0;
}
