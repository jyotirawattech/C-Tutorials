bool* pathExistenceQueries(int n, int* nums, int numsSize, int maxDiff, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    *returnSize = queriesSize;
    
    // Allocate the result array
    bool* answer = (bool*)malloc(queriesSize * sizeof(bool));
    if (!answer) return NULL; // Hardware safety check
    
    // 1. HARDWARE FIX: Flat Component Map
    // Instead of building a complex Disjoint Set Union (DSU) tree, we allocate 
    // a single flat integer array. This guarantees 100% L1 Cache sequential reads.
    int* component_map = (int*)malloc(n * sizeof(int));
    if (!component_map) {
        free(answer);
        return NULL;
    }
    
    // 2. The O(N) Contiguous Component Sweep
    int current_component = 0;
    component_map[0] = current_component;
    
    for (int i = 1; i < n; i++) {
        // If the gap exceeds maxDiff, the topological chain is broken.
        // We increment the ID to start a new isolated graph component.
        if (nums[i] - nums[i - 1] > maxDiff) {
            current_component++;
        }
        // Assign the node to the current active component
        component_map[i] = current_component;
    }
    
    // 3. The O(1) Query Resolution Engine
    // Because the components are mapped to a flat array, resolving a path query
    // requires zero traversal. We simply compare two integer registers.
    for (int i = 0; i < queriesSize; i++) {
        int u = queries[i][0];
        int v = queries[i][1];
        
        answer[i] = (component_map[u] == component_map[v]);
    }
    
    // Free the state tracker memory
    free(component_map);
    
    return answer;
}