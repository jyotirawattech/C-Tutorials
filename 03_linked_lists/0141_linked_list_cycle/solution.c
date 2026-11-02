/**
 * Problem: LeetCode 0141 - Linked List Cycle
 * Language: C (C11)
 *
 * Approach:
 * Floyd's Cycle-Finding Algorithm (Tortoise and Hare).
 * A slow pointer advances 1 node per iteration while a fast pointer advances 2.
 * If a cycle exists, the fast pointer will lap the slow pointer inside the loop.
 *
 * Complexity:
 * - Time: O(N) where N is the total number of nodes.
 * - Space: O(1) auxiliary pointer memory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

bool hasCycle(struct ListNode *head) {
    if (!head || !head->next) {
        return false;
    }

    struct ListNode* slow = head;
    struct ListNode* fast = head->next;

    while (fast != NULL && fast->next != NULL) {
        if (slow == fast) {
            return true;
        }
        slow = slow->next;
        fast = fast->next->next;
    }

    return false;
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

/* ========================================================================= */
/* Standalone Test Harness                                                   */
/* ========================================================================= */

int main(void) {
    printf("[TEST] Running LeetCode 0141: Linked List Cycle...\n");

    // Test Case 1: List with cycle [3, 2, 0, -4] where -4 points to node with val 2
    {
        struct ListNode* n1 = create_node(3);
        struct ListNode* n2 = create_node(2);
        struct ListNode* n3 = create_node(0);
        struct ListNode* n4 = create_node(-4);

        n1->next = n2;
        n2->next = n3;
        n3->next = n4;
        n4->next = n2; // creates cycle

        assert(hasCycle(n1) == true);
        printf("  ✓ Test 1 Passed: [3, 2, 0, -4] (cycle at pos 1) -> true\n");

        // Break cycle before freeing to prevent infinite loop during teardown
        n4->next = NULL;
        free(n1);
        free(n2);
        free(n3);
        free(n4);
    }

    // Test Case 2: List with 2 nodes and cycle [1, 2] -> 1
    {
        struct ListNode* n1 = create_node(1);
        struct ListNode* n2 = create_node(2);
        n1->next = n2;
        n2->next = n1;

        assert(hasCycle(n1) == true);
        printf("  ✓ Test 2 Passed: [1, 2] (cycle at pos 0) -> true\n");

        n2->next = NULL;
        free(n1);
        free(n2);
    }

    // Test Case 3: Single node without cycle [1]
    {
        struct ListNode* n1 = create_node(1);
        assert(hasCycle(n1) == false);
        printf("  ✓ Test 3 Passed: [1] (no cycle) -> false\n");
        free(n1);
    }

    // Test Case 4: Empty list NULL
    {
        assert(hasCycle(NULL) == false);
        printf("  ✓ Test 4 Passed: NULL -> false\n");
    }

    printf("[PASSED] All LeetCode 0141 tests passed with zero leaks!\n\n");
    return 0;
}
