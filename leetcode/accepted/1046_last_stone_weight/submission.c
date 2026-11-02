#include <stdio.h>

// Helper to swap elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble an element UP the tree
void heapify_up(int* heap, int index) {
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

// Bubble an element DOWN the tree
void heapify_down(int* heap, int size, int index) {
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

// Extract the max element
int pop(int* heap, int* size) {
    int max_val = heap[0];
    heap[0] = heap[*size - 1]; // Move last element to root
    (*size)--;
    heapify_down(heap, *size, 0); // Rebalance
    return max_val;
}

// Insert a new element
void push(int* heap, int* size, int val) {
    heap[*size] = val; // Add to end
    (*size)++;
    heapify_up(heap, *size - 1); // Rebalance
}

int lastStoneWeight(int* stones, int stonesSize) {
    // 1. Build the initial Max-Heap in O(N)
    for (int i = (stonesSize / 2) - 1; i >= 0; i--) {
        heapify_down(stones, stonesSize, i);
    }
    
    // 2. Smash stones
    while (stonesSize > 1) {
        int y = pop(stones, &stonesSize);
        int x = pop(stones, &stonesSize);
        
        if (y != x) {
            push(stones, &stonesSize, y - x);
        }
    }
    
    return stonesSize == 0 ? 0 : stones[0];
}