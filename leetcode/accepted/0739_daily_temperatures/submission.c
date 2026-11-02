#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    *returnSize = temperaturesSize;
    
    // calloc initializes all elements to 0 automatically
    int* ans = (int*)calloc(temperaturesSize, sizeof(int));
    
    // Allocate raw memory for the stack
    int* stack = (int*)malloc(temperaturesSize * sizeof(int));
    int top = -1; // -1 indicates an empty stack
    
    for (int i = 0; i < temperaturesSize; i++) {
        while (top >= 0 && temperatures[i] > temperatures[stack[top]]) {
            int prev_idx = stack[top];
            top--; // Pop
            
            ans[prev_idx] = i - prev_idx;
        }
        
        // Push
        stack[++top] = i;
    }
    
    free(stack);
    return ans;
}