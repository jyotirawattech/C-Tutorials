// 1. The Production Approach (Iterative)
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* curr = head;
    struct ListNode* next_temp = NULL;
    
    while (curr != NULL) {
        // 1. Buffer the forward memory address
        next_temp = curr->next;
        
        // 2. Execute the hardware wire flip
        curr->next = prev;
        
        // 3. Slide the mechanical window forward
        prev = curr;
        curr = next_temp;
    }
    
    return prev; // Prev is now pointing to the new head
}

// 2. The Theoretical Approach (Recursive) - DO NOT USE IN PRODUCTION
struct ListNode* reverseListRecursive(struct ListNode* head) {
    // Base case: empty list or we reached the last node
    if (head == NULL || head->next == NULL) {
        return head;
    }
    
    // Push state to the Call Stack until we hit the end
    struct ListNode* new_head = reverseListRecursive(head->next);
    
    // As the stack unwinds, flip the pointer backward
    head->next->next = head;
    
    // Nullify the forward pointer to prevent cycles
    head->next = NULL;
    
    return new_head;
}