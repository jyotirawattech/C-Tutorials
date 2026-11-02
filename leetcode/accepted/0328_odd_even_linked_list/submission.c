#include <stdlib.h>

struct ListNode* oddEvenList(struct ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    
    struct ListNode* odd = head;
    struct ListNode* even = head->next;
    struct ListNode* even_head = even;
    
    while (even != NULL && even->next != NULL) {
        // Wire odd track
        odd->next = even->next;
        odd = odd->next;
        
        // Wire even track
        even->next = odd->next;
        even = even->next;
    }
    
    // Concatenate tails to heads
    odd->next = even_head;
    
    return head;
}