#include <stdlib.h>

int* beautifulArray(int n, int* returnSize) {
    *returnSize = n;
    
    // 1. Allocate the final return array and a temporary working buffer
    int* res = (int*)malloc(n * sizeof(int));
    int* temp = (int*)malloc(n * sizeof(int));
    if (!res || !temp) return NULL; // Hardware safety check
    
    // 2. Base Case: The smallest beautiful array
    res[0] = 1;
    int count = 1;
    
    // 3. The Flattened Recursive Expansion
    while (count < n) {
        int index = 0;
        
        // Branch A: Map the current array to the Left Half (Odds: 2x - 1)
        for (int i = 0; i < count; i++) {
            if (res[i] * 2 - 1 <= n) {
                temp[index++] = res[i] * 2 - 1;
            }
        }
        
        // Branch B: Map the current array to the Right Half (Evens: 2x)
        for (int i = 0; i < count; i++) {
            if (res[i] * 2 <= n) {
                temp[index++] = res[i] * 2;
            }
        }
        
        // Commit the mapped temp buffer back to the main array
        for (int i = 0; i < index; i++) {
            res[i] = temp[i];
        }
        
        // Our beautiful array has now expanded
        count = index;
    }
    
    // Clean up our temporary working memory
    free(temp);
    
    return res;
}