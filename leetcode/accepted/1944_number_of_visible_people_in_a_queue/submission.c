int* canSeePersonsCount(int* heights, int heightsSize, int* returnSize) {
    *returnSize = heightsSize;
    
    // Allocate the result array
    int* ans = (int*)calloc(heightsSize, sizeof(int));
    if (!ans) return NULL; // Hardware safety check

    // 1. HARDWARE FIX: Heap-Allocated Stack
    // The constraints state heightsSize <= 10^5.
    // An array of 100,000 integers is 400 KB. Allocating this directly on the 
    // Call Stack (e.g., `int stack[100000];`) risks a Stack Overflow on 
    // embedded systems or kernel threads. We allocate it safely on the Heap.
    int* stack = (int*)malloc(heightsSize * sizeof(int));
    if (!stack) {
        free(ans);
        return NULL;
    }
    
    // 'top' represents the next empty slot in our stack
    int top = 0; 

    // 2. The Right-to-Left Monotonic Sweep
    for (int i = heightsSize - 1; i >= 0; i--) {
        int visible_count = 0;
        
        // Branch A: Process and Erase Shorter Horizons
        // As long as there are people on the stack and I am taller than them:
        // I can see them, AND I will block anyone to my left from seeing them.
        while (top > 0 && heights[i] > stack[top - 1]) {
            visible_count++;
            top--; // Pop the shorter person out of existence
        }
        
        // Branch B: The Taller Obstruction
        // If the stack isn't empty after popping shorter people, the next person 
        // is TALLER than me. I can see them, but they block my vision completely.
        if (top > 0) {
            visible_count++;
        }
        
        // Record what person 'i' saw
        ans[i] = visible_count;
        
        // Person 'i' now joins the stack to act as a potential horizon 
        // for the people to their left.
        stack[top++] = heights[i];
    }

    // Free our explicit state tracker
    free(stack);
    
    return ans;
}