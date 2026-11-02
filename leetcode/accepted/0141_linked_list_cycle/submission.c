



bool hasCycle(struct ListNode *head) {
    // 1. Initialize our two hardware registers (pointers) at the start
    struct ListNode *slow = head;
    struct ListNode *fast = head;
    
    // 2. The State Machine
    // We must ensure the fast pointer has a valid runway to jump 2 steps.
    // If fast or fast->next becomes NULL, we have hit a dead end (no cycle).
    while (fast != NULL && fast->next != NULL) {
        
        slow = slow->next;          // Tortoise moves 1 step
        fast = fast->next->next;    // Hare moves 2 steps
        
        // 3. The Collision Check
        // Are both pointers looking at the exact same physical memory address?
        if (slow == fast) {
            return true; // Cycle definitively proven
        }
    }
    
    // Fast pointer successfully escaped the list
    return false;
}