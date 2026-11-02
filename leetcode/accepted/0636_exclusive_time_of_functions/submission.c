#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* exclusiveTime(int n, char ** logs, int logsSize, int* returnSize) {
    int* res = (int*)calloc(n, sizeof(int));
    *returnSize = n;
    
    // Stack maximum depth is half the logs (every start has an end)
    int* stack = (int*)malloc((logsSize / 2 + 1) * sizeof(int));
    int top = -1;
    int prev_time = 0;
    
    for (int i = 0; i < logsSize; i++) {
        int id = 0, time = 0;
        char type = 0; 
        
        char* ptr = logs[i];
        
        // Extract ID
        while (*ptr != ':') {
            id = id * 10 + (*ptr - '0');
            ptr++;
        }
        ptr++; // Skip ':'
        
        // Extract Type ('s' or 'e')
        type = *ptr;
        if (type == 's') ptr += 6; // Skip "start:"
        else ptr += 4;             // Skip "end:"
        
        // Extract Time
        while (*ptr != '\0') {
            time = time * 10 + (*ptr - '0');
            ptr++;
        }
        
        // Execute State Machine
        if (type == 's') {
            if (top >= 0) {
                res[stack[top]] += time - prev_time;
            }
            stack[++top] = id; // Push
            prev_time = time;
        } else {
            res[stack[top--]] += time - prev_time + 1; // Pop
            prev_time = time + 1;
        }
    }
    
    free(stack);
    return res;
}