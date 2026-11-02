#include <stdlib.h>
#include <limits.h>

// 1. Safe Hardware Comparator for qsort
int compare(const void* a, const void* b) {
    int int_a = *(const int*)a;
    int int_b = *(const int*)b;
    // Do not use (a - b) to avoid integer overflow edge cases
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

int** minimumAbsDifference(int* arr, int arrSize, int* returnSize, int** returnColumnSizes) {
    // Phase 1: Sort to bring closest pairs adjacent
    qsort(arr, arrSize, sizeof(int), compare);
    
    int min_diff = INT_MAX;
    int count = 0;
    
    // Phase 2: Scout Pass - Find the minimum difference and count occurrences
    for (int i = 0; i < arrSize - 1; i++) {
        int diff = arr[i+1] - arr[i];
        if (diff < min_diff) {
            min_diff = diff;
            count = 1;       // Reset count because we found a new smaller difference
        } else if (diff == min_diff) {
            count++;         // Increment count for the current minimum difference
        }
    }
    
    // Phase 3: Exact Memory Allocation (Zero realloc overhead)
    *returnSize = count;
    int** result = (int**)malloc(count * sizeof(int*));
    *returnColumnSizes = (int*)malloc(count * sizeof(int));
    
    // Phase 4: Populate Pass
    int index = 0;
    for (int i = 0; i < arrSize - 1; i++) {
        if (arr[i+1] - arr[i] == min_diff) {
            result[index] = (int*)malloc(2 * sizeof(int));
            result[index][0] = arr[i];
            result[index][1] = arr[i+1];
            (*returnColumnSizes)[index] = 2; // Every pair has exactly 2 columns
            index++;
        }
    }
    
    return result;
}