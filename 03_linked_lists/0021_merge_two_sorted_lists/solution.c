/**
 * Problem: LeetCode 0021 - Merge Two Sorted Lists
 * Language: C (C11)
 *
 * Approach:
 * Uses a stack-allocated sentinel dummy node to eliminate edge-case branching
 * for the new list head. Merges existing node pointers directly without allocating
 * any new nodes (zero heap allocation during merge).
 *
 * Complexity:
 * - Time: O(M + N) where M and N are lengths of the lists.
 * - Space: O(1) in-place pointer splicing.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    struct ListNode dummy;
    dummy.next = NULL;
    struct ListNode* tail = &dummy;

    while (list1 != NULL && list2 != NULL) {
        if (list1->val <= list2->val) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    tail->next = (list1 != NULL) ? list1 : list2;
    return dummy.next;
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
    printf("[TEST] Running LeetCode 0021: Merge Two Sorted Lists...\n");

    // Test Case 1: [1, 2, 4] and [1, 3, 4] -> [1, 1, 2, 3, 4, 4]
    {
        int v1[] = {1, 2, 4};
        int v2[] = {1, 3, 4};
        int expected[] = {1, 1, 2, 3, 4, 4};
        struct ListNode* l1 = build_list(v1, 3);
        struct ListNode* l2 = build_list(v2, 3);

        struct ListNode* merged = mergeTwoLists(l1, l2);
        assert_list_equals(merged, expected, 6);
        free_list(merged);
        printf("  ✓ Test 1 Passed: [1,2,4] + [1,3,4] -> [1,1,2,3,4,4]\n");
    }

    // Test Case 2: [] and [] -> []
    {
        struct ListNode* merged = mergeTwoLists(NULL, NULL);
        assert(merged == NULL);
        printf("  ✓ Test 2 Passed: [] + [] -> []\n");
    }

    // Test Case 3: [] and [0] -> [0]
    {
        int v2[] = {0};
        int expected[] = {0};
        struct ListNode* l2 = build_list(v2, 1);
        struct ListNode* merged = mergeTwoLists(NULL, l2);
        assert_list_equals(merged, expected, 1);
        free_list(merged);
        printf("  ✓ Test 3 Passed: [] + [0] -> [0]\n");
    }

    printf("[PASSED] All LeetCode 0021 tests passed with zero leaks!\n\n");
    return 0;
}
