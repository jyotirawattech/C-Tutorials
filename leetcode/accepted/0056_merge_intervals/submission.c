#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

// 1. Hardware-Safe Comparator for 2D Array Sorting
int compare(const void* a, const void* b) {
    int* intervalA = *(int**)a;
    int* intervalB = *(int**)b;
    // Compare by Start Time
    return intervalA[0] - intervalB[0];
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {
    if (intervalsSize == 0) {
        *returnSize = 0;
        return NULL;
    }

    // 2. Sort the memory sequentially to ensure L1 Cache locality during the sweep
    qsort(intervals, intervalsSize, sizeof(int*), compare);

    // 3. The In-Place Accordion Compaction
    int write_idx = 0;
    
    for (int read_idx = 1; read_idx < intervalsSize; read_idx++) {
        // If the scout block overlaps with the active write block
        if (intervals[write_idx][1] >= intervals[read_idx][0]) {
            // Absorb the block by extending the right boundary
            intervals[write_idx][1] = MAX(intervals[write_idx][1], intervals[read_idx][1]);
        } else {
            // No overlap. Lock the current block, move the write head forward.
            write_idx++;
            // Physically copy the new block into the compacted region of the array
            intervals[write_idx][0] = intervals[read_idx][0];
            intervals[write_idx][1] = intervals[read_idx][1];
        }
    }

    // 4. Exact Final Allocation
    // The write pointer index + 1 is the exact number of merged intervals
    int final_count = write_idx + 1;
    *returnSize = final_count;

    // Allocate exact memory for the OS (Zero heap fragmentation)
    int** result = (int**)malloc(final_count * sizeof(int*));
    *returnColumnSizes = (int*)malloc(final_count * sizeof(int));

    for (int i = 0; i < final_count; i++) {
        result[i] = (int*)malloc(2 * sizeof(int));
        result[i][0] = intervals[i][0];
        result[i][1] = intervals[i][1];
        (*returnColumnSizes)[i] = 2; // LeetCode metadata requirement
    }

    return result;
}