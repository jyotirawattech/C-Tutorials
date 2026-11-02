#include <stdlib.h>

struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode* curr = head;
    
    while (curr != NULL && curr->next != NULL) {
        if (curr->val == curr->next->val) {
            // Capture the orphaned memory
            struct ListNode* memory_leak = curr->next;
            
            // Bypass
            curr->next = curr->next->next;
            
            // Prevent the memory leak
            free(memory_leak);
        } else {
            curr = curr->next;
        }
    }
    
    return head;
}