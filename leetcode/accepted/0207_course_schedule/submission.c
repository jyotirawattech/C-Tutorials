typedef struct Node {
    int val;
    struct Node* next;
} Node;

bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize) {
    // 1. HARDWARE FIX: The Contiguous Edge Pool
    // Instead of doing 'malloc' 5000 times, we allocate exactly one contiguous block
    // of memory to hold all possible edges. This prevents heap fragmentation.
    Node* edge_pool = (Node*)malloc(prerequisitesSize * sizeof(Node));
    Node** adj = (Node**)calloc(numCourses, sizeof(Node*));
    int* in_degree = (int*)calloc(numCourses, sizeof(int));
    
    // Safety check for memory allocation
    if (!adj || !in_degree || (prerequisitesSize > 0 && !edge_pool)) return false;

    // 2. Build the Graph
    for (int i = 0; i < prerequisitesSize; i++) {
        int course = prerequisites[i][0];
        int prereq = prerequisites[i][1];
        
        // Directed edge: prereq -> course (Prereq unlocks Course)
        edge_pool[i].val = course;
        edge_pool[i].next = adj[prereq];
        adj[prereq] = &edge_pool[i];
        
        // This course requires one more thing before it can run
        in_degree[course]++;
    }

    // 3. Stack-Allocated Queue (Zero latency, fixed size)
    // The constraints state numCourses <= 2000. This perfectly fits on the Call Stack.
    int queue[2000];
    int head = 0, tail = 0;

    // 4. Seed the Execution Queue with Independent Tasks
    for (int i = 0; i < numCourses; i++) {
        if (in_degree[i] == 0) {
            queue[tail++] = i; // Ready to execute immediately
        }
    }

    int processed_count = 0;

    // 5. Kahn's Topological State Machine
    while (head < tail) {
        int curr = queue[head++];
        processed_count++; // Mark task as completed

        // Traverse all tasks that were waiting on this current task
        Node* neighbor = adj[curr];
        while (neighbor != NULL) {
            int next_course = neighbor->val;
            
            // Remove the dependency
            in_degree[next_course]--;
            
            // If the dependent task now has NO prerequisites, it is ready to execute
            if (in_degree[next_course] == 0) {
                queue[tail++] = next_course;
            }
            neighbor = neighbor->next;
        }
    }

    // 6. Memory Cleanup
    free(adj);
    free(in_degree);
    if (prerequisitesSize > 0) free(edge_pool);

    // If we processed all courses, there was no cyclic deadlock
    return processed_count == numCourses;
}