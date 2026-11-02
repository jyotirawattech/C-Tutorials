#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* finalPrices(int* prices, int pricesSize, int* returnSize) {
    *returnSize = pricesSize;
    
    // Allocate exact memory for the stack
    int* stack = (int*)malloc(pricesSize * sizeof(int));
    int top = -1; // -1 indicates an empty stack
    
    for (int i = 0; i < pricesSize; i++) {
        // Check if current price can resolve pending discounts
        while (top >= 0 && prices[stack[top]] >= prices[i]) {
            int pending_idx = stack[top];
            prices[pending_idx] -= prices[i]; // Mutate in-place
            top--; // Pop from stack
        }
        
        // Push current index
        stack[++top] = i;
    }
    
    // Free the auxiliary memory
    free(stack);
    
    // Return the mutated original array
    return prices;
}