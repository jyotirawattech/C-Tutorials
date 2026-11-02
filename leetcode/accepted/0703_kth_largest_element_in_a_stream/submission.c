#include <stdlib.h>

typedef struct {
    int* heap;
    int size;
    int k;
} KthLargest;

// Helper to swap two integers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Helper: Bubble up the newly added element to maintain Min-Heap property
void heapifyUp(int* heap, int index) {
    int parent = (index - 1) / 2;
    // If current node is smaller than parent, swap and continue up
    if (index > 0 && heap[index] < heap[parent]) {
        swap(&heap[index], &heap[parent]);
        heapifyUp(heap, parent);
    }
}

// Helper: Bubble down an element to maintain Min-Heap property
void heapifyDown(int* heap, int size, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Find the smallest among the root, left child, and right child
    if (left < size && heap[left] < heap[smallest]) {
        smallest = left;
    }
    if (right < size && heap[right] < heap[smallest]) {
        smallest = right;
    }

    // If the root wasn't the smallest, swap and continue down
    if (smallest != index) {
        swap(&heap[index], &heap[smallest]);
        heapifyDown(heap, size, smallest);
    }
}

// "Constructor"
KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
    KthLargest* obj = (KthLargest*)malloc(sizeof(KthLargest));
    // We only ever need an array of size k!
    obj->heap = (int*)malloc(k * sizeof(int));
    obj->size = 0;
    obj->k = k;

    // Forward declare the add function so we can use it here
    int kthLargestAdd(KthLargest* obj, int val);

    for (int i = 0; i < numsSize; i++) {
        kthLargestAdd(obj, nums[i]);
    }
    return obj;
}

int kthLargestAdd(KthLargest* obj, int val) {
    // Phase 1: The heap isn't full yet. Just insert and bubble up.
    if (obj->size < obj->k) {
        obj->heap[obj->size] = val;
        heapifyUp(obj->heap, obj->size);
        obj->size++;
    } 
    // Phase 2: The heap is full. 
    // Only process the new value if it's larger than our minimum element.
    else if (val > obj->heap[0]) {
        obj->heap[0] = val; // Overwrite the root (the minimum)
        heapifyDown(obj->heap, obj->size, 0); // Bubble the new value down
    }
    
    // The root is always the K-th largest element
    return obj->heap[0];
}

// "Destructor"
void kthLargestFree(KthLargest* obj) {
    free(obj->heap);
    free(obj);
}