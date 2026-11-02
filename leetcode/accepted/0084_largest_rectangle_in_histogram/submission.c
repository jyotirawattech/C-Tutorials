#include <stdlib.h>

int largestRectangleArea(int* heights, int heightsSize) {
    int max_area = 0;
    
    // Allocate raw stack for indices
    int* stack = (int*)malloc((heightsSize + 1) * sizeof(int));
    int top = -1; // Empty stack indicator
    
    for (int i = 0; i <= heightsSize; i++) {
        int current_height = (i == heightsSize) ? 0 : heights[i];
        
        while (top != -1 && current_height < heights[stack[top]]) {
            int h = heights[stack[top]];
            top--; // Pop
            
            int w = (top == -1) ? i : i - stack[top] - 1;
            int area = h * w;
            
            if (area > max_area) {
                max_area = area;
            }
        }
        
        stack[++top] = i; // Push
    }
    
    free(stack);
    return max_area;
}