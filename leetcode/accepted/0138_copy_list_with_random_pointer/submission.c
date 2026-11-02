struct Node* copyRandomList(struct Node* head) {
    if (head == NULL) return NULL;

    // PHASE 1: WEAVE (A -> A' -> B -> B')
    struct Node* curr = head;
    while (curr != NULL) {
        // Note: malloc and NULL are automatically handled by the platform's includes
        struct Node* clone = (struct Node*)malloc(sizeof(struct Node));
        clone->val = curr->val;
        clone->random = NULL; 
        
        // Splice the clone into the chain
        clone->next = curr->next;
        curr->next = clone;
        
        // Jump over the newly inserted clone
        curr = clone->next;
    }

    // PHASE 2: RANDOM WIRE
    curr = head;
    while (curr != NULL) {
        if (curr->random != NULL) {
            // The clone's random is the original's random's next (which is the clone's random)
            curr->next->random = curr->random->next;
        }
        // Jump to the next original node
        curr = curr->next->next;
    }

    // PHASE 3: UNWEAVE
    curr = head;
    struct Node* clone_head = head->next;
    struct Node* clone_curr = clone_head;

    while (curr != NULL) {
        // Restore original list's next pointer
        curr->next = curr->next->next;
        
        // Wire clone list's next pointer (handling the tail safely)
        if (clone_curr->next != NULL) {
            clone_curr->next = clone_curr->next->next;
        }
        
        // Advance both pointers
        curr = curr->next;
        clone_curr = clone_curr->next;
    }

    return clone_head;
}