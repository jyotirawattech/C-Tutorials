#include <stdlib.h>

typedef struct {
    int sum;
    int i;
    int j;
} Item;

void swap(Item* a, Item* b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(Item* heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].sum < heap[parent].sum) {
            swap(&heap[index], &heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void heapify_down(Item* heap, int size, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap[left].sum < heap[smallest].sum) smallest = left;
    if (right < size && heap[right].sum < heap[smallest].sum) smallest = right;

    if (smallest != index) {
        swap(&heap[index], &heap[smallest]);
        heapify_down(heap, size, smallest);
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** kSmallestPairs(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize, int** returnColumnSizes) {
    // Determine the maximum practical limit for rows
    int limit = nums1Size < k ? nums1Size : k;
    
    Item* heap = (Item*)malloc(limit * sizeof(Item));
    int heap_size = 0;
    
    // Push initial column
    for (int i = 0; i < limit; i++) {
        heap[heap_size].sum = nums1[i] + nums2[0];
        heap[heap_size].i = i;
        heap[heap_size].j = 0;
        heapify_up(heap, heap_size);
        heap_size++;
    }
    
    // --- THE HARDWARE FIX ---
    // Force the ALU to use 64-bit registers for the multiplication to prevent overflow
    long long total_pairs = (long long)nums1Size * (long long)nums2Size;
    int max_results = total_pairs < k ? (int)total_pairs : k;
    // ------------------------

    // Allocate results
    int** res = (int**)malloc(max_results * sizeof(int*));
    *returnColumnSizes = (int*)malloc(max_results * sizeof(int));
    *returnSize = 0;
    
    while (k > 0 && heap_size > 0) {
        // Pop Min
        Item min_item = heap[0];
        heap[0] = heap[heap_size - 1];
        heap_size--;
        heapify_down(heap, heap_size, 0);
        
        // Record Result
        res[*returnSize] = (int*)malloc(2 * sizeof(int));
        res[*returnSize][0] = nums1[min_item.i];
        res[*returnSize][1] = nums2[min_item.j];
        (*returnColumnSizes)[*returnSize] = 2;
        (*returnSize)++;
        
        // Push next element in the row
        if (min_item.j + 1 < nums2Size) {
            heap[heap_size].sum = nums1[min_item.i] + nums2[min_item.j + 1];
            heap[heap_size].i = min_item.i;
            heap[heap_size].j = min_item.j + 1;
            heapify_up(heap, heap_size);
            heap_size++;
        }
        k--;
    }
    
    free(heap);
    return res;
}