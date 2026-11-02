#include <stdlib.h>

typedef struct {
    int** indices;  // Array of pointers to index lists
    int* counts;    // Current length/capacity of each index list
} RangeFreqQuery;

RangeFreqQuery* rangeFreqQueryCreate(int* arr, int arrSize) {
    RangeFreqQuery* obj = (RangeFreqQuery*)malloc(sizeof(RangeFreqQuery));
    
    // Allocate 10001 slots for constraints (1 <= value <= 10000)
    obj->indices = (int**)calloc(10001, sizeof(int*));
    obj->counts = (int*)calloc(10001, sizeof(int));
    
    // PASS 1: Count exact frequencies to avoid dynamic resizing
    for (int i = 0; i < arrSize; ++i) {
        obj->counts[arr[i]]++;
    }
    
    // Allocate exact memory for each value's index list
    for (int i = 0; i <= 10000; ++i) {
        if (obj->counts[i] > 0) {
            obj->indices[i] = (int*)malloc(obj->counts[i] * sizeof(int));
            obj->counts[i] = 0; // Reset count so we can use it as an insert cursor
        }
    }
    
    // PASS 2: Populate the indices (naturally sorted because 'i' goes 0 to n)
    for (int i = 0; i < arrSize; ++i) {
        int val = arr[i];
        obj->indices[val][obj->counts[val]++] = i;
    }
    
    return obj;
}

// Custom Lower Bound: First element >= target
int lower_bound(int* arr, int size, int target) {
    int l = 0, r = size;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] >= target) r = mid;
        else l = mid + 1;
    }
    return l;
}

// Custom Upper Bound: First element > target
int upper_bound(int* arr, int size, int target) {
    int l = 0, r = size;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] > target) r = mid;
        else l = mid + 1;
    }
    return l;
}

int rangeFreqQueryQuery(RangeFreqQuery* obj, int left, int right, int value) {
    // If the value doesn't exist in our arrays, return 0
    if (obj->counts[value] == 0) {
        return 0;
    }
    
    int* list = obj->indices[value];
    int size = obj->counts[value];
    
    int l_idx = lower_bound(list, size, left);
    int r_idx = upper_bound(list, size, right);
    
    return r_idx - l_idx;
}

void rangeFreqQueryFree(RangeFreqQuery* obj) {
    for (int i = 0; i <= 10000; ++i) {
        if (obj->indices[i] != NULL) {
            free(obj->indices[i]);
        }
    }
    free(obj->indices);
    free(obj->counts);
    free(obj);
}