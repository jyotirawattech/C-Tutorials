#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** buildArray(int* target, int targetSize, int n, int* returnSize) {
    // Calculate max possible operations (2 * highest target number)
    int max_ops = target[targetSize - 1] * 2;
    
    // Allocate only an array of pointers (NOT the strings themselves)
    char** ans = (char**)malloc(max_ops * sizeof(char*));
    int count = 0;
    int target_ptr = 0;
    
    for (int stream_num = 1; stream_num <= n; stream_num++) {
        if (target_ptr >= targetSize) {
            break;
        }
        
        if (target[target_ptr] == stream_num) {
            // Point directly to the string literal in read-only memory
            ans[count++] = "Push";
            target_ptr++;
        } else {
            ans[count++] = "Push";
            ans[count++] = "Pop";
        }
    }
    
    *returnSize = count;
    return ans;
}