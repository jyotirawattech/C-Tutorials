#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static void siftDown(int *heap, size_t length, size_t root) {
    int value = heap[root];
    while (root < length / 2) {
        size_t child = 2 * root + 1;
        size_t right = child + 1;
        if (right < length && heap[right] < heap[child]) {
            child = right;
        }
        if (heap[child] >= value) {
            break;
        }
        heap[root] = heap[child];
        root = child;
    }
    heap[root] = value;
}

/*
 * values, scratch, and result must name separate valid storage.
 * rank is one-based. Only the first rank scratch slots are used.
 */
bool selectKthLargest(const int *values, size_t count, size_t rank,
                      int *scratch, size_t capacity, int *result) {
    if (values == NULL || scratch == NULL || result == NULL ||
        rank == 0 || rank > count || rank > capacity ||
        count > SIZE_MAX / sizeof *values || capacity > SIZE_MAX / sizeof *scratch) {
        return false;
    }

    for (size_t i = 0; i < rank; ++i) {
        scratch[i] = values[i];
    }
    for (size_t parent = rank / 2; parent > 0; --parent) {
        siftDown(scratch, rank, parent - 1);
    }
    for (size_t i = rank; i < count; ++i) {
        if (values[i] > scratch[0]) {
            scratch[0] = values[i];
            siftDown(scratch, rank, 0);
        }
    }
    *result = scratch[0];
    return true;
}

#ifndef KTH_LARGEST_NO_TEST_MAIN
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int ascending(const void *left, const void *right) {
    int a = *(const int *)left;
    int b = *(const int *)right;
    return (a > b) - (a < b);
}

static size_t testSmallRanks(void) {
    const int alphabet[] = {INT_MIN, 0, INT_MAX};
    size_t arrangements = 1;
    size_t cases = 0;
    for (size_t n = 1; n <= 6; ++n) {
        arrangements *= 3;
        for (size_t code = 0; code < arrangements; ++code) {
            int values[6];
            int ordered[6];
            int original[6];
            size_t digits = code;
            for (size_t i = 0; i < n; ++i) {
                values[i] = alphabet[digits % 3];
                digits /= 3;
            }
            memcpy(ordered, values, n * sizeof *values);
            memcpy(original, values, n * sizeof *values);
            qsort(ordered, n, sizeof *ordered, ascending);
            for (size_t rank = 1; rank <= n; ++rank) {
                int scratch[7];
                for (size_t i = 0; i < 7; ++i) {
                    scratch[i] = 87;
                }
                int result = 0;
                assert(selectKthLargest(values, n, rank, scratch, 7, &result));
                assert(result == ordered[n - rank]);
                for (size_t i = rank; i < 7; ++i) {
                    assert(scratch[i] == 87);
                }
                assert(memcmp(values, original, n * sizeof *values) == 0);
                ++cases;
            }
        }
    }
    return cases;
}

static void testBoundaries(void) {
    const int values[] = {4, -2, 6};
    int scratch[] = {61, 62, 63};
    int result = 64;
    assert(!selectKthLargest(values, 3, 0, scratch, 3, &result));
    assert(!selectKthLargest(values, 0, 1, scratch, 3, &result));
    assert(!selectKthLargest(values, 3, 4, scratch, 3, &result));
    assert(!selectKthLargest(values, 3, 2, scratch, 1, &result));
    assert(!selectKthLargest(NULL, 3, 2, scratch, 3, &result));
    assert(!selectKthLargest(values, 3, 2, NULL, 3, &result));
    assert(!selectKthLargest(values, 3, 2, scratch, 3, NULL));
    if (sizeof(int) > 1) {
        size_t oversized = SIZE_MAX / sizeof(int) + 1;
        assert(!selectKthLargest(values, oversized, 2, scratch, 3, &result));
        assert(!selectKthLargest(values, 3, 2, scratch, oversized, &result));
    }
    assert(result == 64 && scratch[0] == 61 && scratch[1] == 62 && scratch[2] == 63);
}

static void testIncreasingInput(void) {
    int values[1024];
    int scratch[32];
    for (size_t i = 0; i < 1024; ++i) {
        values[i] = (int)i;
    }
    int result = -1;
    assert(selectKthLargest(values, 1024, 32, scratch, 32, &result));
    assert(result == 992);
    for (size_t i = 0; i < 1024; ++i) {
        assert(values[i] == (int)i);
    }
}

int main(void) {
    size_t cases = testSmallRanks();
    testBoundaries();
    testIncreasingInput();
    printf("[PASSED] Kth Largest: %zu sort oracle cases, guarded scratch and read-only input.\n", cases);
    return 0;
}
#endif
