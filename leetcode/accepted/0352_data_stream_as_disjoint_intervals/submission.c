#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int parent[10005];
    bool seen[10005];
} SummaryRanges;

SummaryRanges* summaryRangesCreate() {
    SummaryRanges* obj = (SummaryRanges*)calloc(1, sizeof(SummaryRanges));
    // Initially, every number is its own parent/root
    for (int i = 0; i <= 10001; i++) {
        obj->parent[i] = i;
    }
    return obj;
}

// Find with Path Compression
int find(SummaryRanges* obj, int i) {
    if (obj->parent[i] == i) {
        return i;
    }
    // Compress the path so future lookups are instant
    return obj->parent[i] = find(obj, obj->parent[i]);
}

void summaryRangesAddNum(SummaryRanges* obj, int value) {
    if (obj->seen[value]) return; // Already processed
    
    obj->seen[value] = true;
    
    // If the number above us exists, merge into its group
    if (value < 10004 && obj->seen[value + 1]) {
        obj->parent[value] = find(obj, value + 1);
    }
    
    // If the number below us exists, link its root to our root
    // Our root is now the highest number in the contiguous chain
    if (value > 0 && obj->seen[value - 1]) {
        obj->parent[find(obj, value - 1)] = find(obj, value);
    }
}

int** summaryRangesGetIntervals(SummaryRanges* obj, int* retSize, int** retColSize) {
    // Allocate max possible intervals
    int** intervals = (int**)malloc(10005 * sizeof(int*));
    *retColSize = (int*)malloc(10005 * sizeof(int));
    int count = 0;
    
    for (int i = 0; i <= 10000; i++) {
        if (obj->seen[i]) {
            intervals[count] = (int*)malloc(2 * sizeof(int));
            intervals[count][0] = i; // The start of the interval
            
            // The DSU find() function instantly gives us the end of the interval
            int end = find(obj, i); 
            intervals[count][1] = end;
            
            (*retColSize)[count] = 2;
            count++;
            
            // Fast-forward our loop to the end of this newly discovered interval!
            i = end; 
        }
    }
    
    *retSize = count;
    return intervals;
}

void summaryRangesFree(SummaryRanges* obj) {
    free(obj);
}