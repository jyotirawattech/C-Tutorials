#include <stdlib.h>

struct ListNode* insertionSortList(struct ListNode* head) {
    // Base Case: An empty list or single-node list is inherently sorted
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // 1. The Dummy Anchor (Allocated safely on the Call Stack)
    struct ListNode dummy = {0, NULL}; 
    
    // 'curr' tracks our progress through the original, unsorted list
    struct ListNode* curr = head;

    while (curr != NULL) {
        // Step A: Save the next unsorted node before we break the current pointer!
        struct ListNode* next_node = curr->next;
        
        // Step B: Reset our scout to the Dummy Anchor
        struct ListNode* prev = &dummy;
        
        // Step C: Scout forward until we find a node LARGER than our curr node
        // (This finds the exact gap where curr belongs)
        while (prev->next != NULL && prev->next->val < curr->val) {
            prev = prev->next;
        }
        
        // Step D: The O(1) Pointer Splice
        // 1. Point curr's next to the larger node
        curr->next = prev->next;
        // 2. Point the smaller node's next to curr
        prev->next = curr;
        
        // Step E: Advance our unsorted list processor
        curr = next_node;
    }

    // Return the true head, cleanly bypassing our Dummy Anchor
    return dummy.next;
}