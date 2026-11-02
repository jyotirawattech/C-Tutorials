#include <stdbool.h>
#include <stdlib.h>

void swap(long long* a, long long* b) {
    long long temp = *a; 
    *a = *b; 
    *b = temp;
}

void heapify_down(long long* heap, int size, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap[left] > heap[largest]) largest = left;
    if (right < size && heap[right] > heap[largest]) largest = right;

    if (largest != index) {
        swap(&heap[index], &heap[largest]);
        heapify_down(heap, size, largest);
    }
}

void heapify_up(long long* heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index] > heap[parent]) {
            swap(&heap[index], &heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

bool isPossible(int* target, int targetSize) {
    // Edge case: If there is only one element, it must be exactly 1.
    if (targetSize == 1) return target[0] == 1;

    long long* heap = (long long*)malloc(targetSize * sizeof(long long));
    long long total_sum = 0;

    for (int i = 0; i < targetSize; i++) {
        heap[i] = (long long)target[i];
        total_sum += heap[i];
    }

    // Build Max-Heap in O(N) time
    for (int i = (targetSize / 2) - 1; i >= 0; i--) {
        heapify_down(heap, targetSize, i);
    }

    // Process the backwards state machine
    while (heap[0] > 1) {
        long long max_val = heap[0];
        long long rest = total_sum - max_val;

        // If the remaining sum is 1, it will always eventually reduce to [1, 1... 1]
        if (rest == 1) {
            free(heap);
            return true;
        }
        
        // If the remaining elements sum to 0, or the current max is smaller than the rest, 
        // the state is invalid and impossible to reach.
        if (rest == 0 || max_val <= rest) {
            free(heap);
            return false;
        }

        // Calculate the previous state of the maximum element
        long long prev_val = max_val % rest;
        
        // If the previous value is 0 (and rest != 1), it means it was a perfect multiple, 
        // which breaks the starting condition of 1s.
        if (prev_val == 0) {
            free(heap);
            return false;
        }

        // IN-PLACE REPLACEMENT: Overwrite the root directly and rebalance once.
        heap[0] = prev_val;
        heapify_down(heap, targetSize, 0);
        
        // Update the global running sum
        total_sum = rest + prev_val;
    }

    free(heap);
    return true;
}