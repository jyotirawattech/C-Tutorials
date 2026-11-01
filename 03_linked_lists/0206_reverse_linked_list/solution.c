/**
 * Problem: LeetCode 0206 - Reverse Linked List
 * Language: C (C11)
 *
 * Approach:
 * Iterative three-pointer pointer rewiring (prev, curr, next).
 * In-place reversal modifying pointer bindings without extra node allocations.
 *
 * Complexity:
 * - Time: O(N) where N is the number of nodes in the list.
 * - Space: O(1) in-place auxiliary space.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* curr = head;

    while (curr != NULL) {
        struct ListNode* next_node = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next_node;
    }

    return prev;
}

/* ========================================================================= */
/* Test Harness Helper Functions                                             */
/* ========================================================================= */

static struct ListNode* create_node(int val) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    assert(node != NULL);
    node->val = val;
    node->next = NULL;
    return node;
}

static struct ListNode* build_list(const int* values, int count) {
    if (count == 0) return NULL;
    struct ListNode* head = create_node(values[0]);
    struct ListNode* tail = head;
    for (int i = 1; i < count; i++) {
        tail->next = create_node(values[i]);
        tail = tail->next;
    }
    return head;
}

static void free_list(struct ListNode* head) {
    while (head != NULL) {
        struct ListNode* tmp = head;
        head = head->next;
        free(tmp);
    }
}

static void assert_list_equals(const struct ListNode* head, const int* expected, int count) {
    const struct ListNode* curr = head;
    for (int i = 0; i < count; i++) {
        assert(curr != NULL);
        assert(curr->val == expected[i]);
        curr = curr->next;
    }
    assert(curr == NULL);
}

/* ========================================================================= */
/* Standalone Test Harness                                                   */
/* ========================================================================= */

int main(void) {
    printf("[TEST] Running LeetCode 0206: Reverse Linked List...\n");

    // Test Case 1: Standard 5-element list [1, 2, 3, 4, 5] -> [5, 4, 3, 2, 1]
    {
        int values[] = {1, 2, 3, 4, 5};
        int expected[] = {5, 4, 3, 2, 1};
        struct ListNode* list = build_list(values, 5);
        struct ListNode* reversed = reverseList(list);
        assert_list_equals(reversed, expected, 5);
        free_list(reversed);
        printf("  ✓ Test 1 Passed: [1, 2, 3, 4, 5] -> [5, 4, 3, 2, 1]\n");
    }

    // Test Case 2: 2-element list [1, 2] -> [2, 1]
    {
        int values[] = {1, 2};
        int expected[] = {2, 1};
        struct ListNode* list = build_list(values, 2);
        struct ListNode* reversed = reverseList(list);
        assert_list_equals(reversed, expected, 2);
        free_list(reversed);
        printf("  ✓ Test 2 Passed: [1, 2] -> [2, 1]\n");
    }

    // Test Case 3: Empty list NULL -> NULL
    {
        struct ListNode* reversed = reverseList(NULL);
        assert(reversed == NULL);
        printf("  ✓ Test 3 Passed: [] -> []\n");
    }

    // Test Case 4: Single element list [42] -> [42]
    {
        int values[] = {42};
        int expected[] = {42};
        struct ListNode* list = build_list(values, 1);
        struct ListNode* reversed = reverseList(list);
        assert_list_equals(reversed, expected, 1);
        free_list(reversed);
        printf("  ✓ Test 4 Passed: [42] -> [42]\n");
    }

    printf("[PASSED] All LeetCode 0206 tests passed with zero leaks!\n\n");
    return 0;
}
