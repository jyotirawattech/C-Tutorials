#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum {
    MISSING_NUMBERS_OK,
    MISSING_NUMBERS_INVALID,
    MISSING_NUMBERS_ALLOCATION_FAILURE
} MissingStatus;

typedef struct {
    int *numbers;
    size_t count;
} MissingNumbers;

#ifndef MISSING_NUMBERS_MALLOC
#ifdef MISSING_NUMBERS_NO_TEST_MAIN
#define MISSING_NUMBERS_MALLOC malloc
#else
static size_t allocation_calls;
static size_t requested_bytes;
static int fail_allocation;

static void *testAllocate(size_t bytes) {
    ++allocation_calls;
    requested_bytes = bytes;
    return fail_allocation ? NULL : malloc(bytes);
}
#define MISSING_NUMBERS_MALLOC testAllocate
#endif
#endif

/*
 * values is exclusively writable during the call and never aliases result.
 * On success, the caller owns result->numbers and may free it.
 * On error, result is unchanged. The input's values are restored on return.
 */
MissingStatus findMissingNumbers(int *values, size_t count, MissingNumbers *result) {
    if (result == NULL || (values == NULL && count != 0) ||
        count > INT_MAX || count > SIZE_MAX / sizeof *values) {
        return MISSING_NUMBERS_INVALID;
    }
    for (size_t i = 0; i < count; ++i) {
        if (values[i] <= 0 || values[i] > (int)count) {
            return MISSING_NUMBERS_INVALID;
        }
    }

    size_t missing = count;
    for (size_t i = 0; i < count; ++i) {
        int value = values[i] < 0 ? -values[i] : values[i];
        size_t marker = (size_t)value - 1;
        if (values[marker] > 0) {
            values[marker] = -values[marker];
            --missing;
        }
    }

    int *numbers = missing == 0 ? NULL : MISSING_NUMBERS_MALLOC(missing * sizeof *numbers);
    size_t written = 0;
    for (size_t i = 0; i < count; ++i) {
        if (values[i] < 0) {
            values[i] = -values[i];
        } else if (numbers != NULL) {
            numbers[written++] = (int)(i + 1);
        }
    }

    if (missing != 0 && numbers == NULL) {
        return MISSING_NUMBERS_ALLOCATION_FAILURE;
    }
    *result = (MissingNumbers){.numbers = numbers, .count = missing};
    return MISSING_NUMBERS_OK;
}

#ifndef MISSING_NUMBERS_NO_TEST_MAIN
#include <assert.h>
#include <stdio.h>
#include <string.h>

static void resetAllocator(void) {
    allocation_calls = 0;
    requested_bytes = 0;
    fail_allocation = 0;
}

static void checkMissing(int *values, size_t count) {
    assert(count <= 6);
    int original[6];
    int expected[6];
    size_t expected_count = 0;
    for (size_t i = 0; i < count; ++i) {
        original[i] = values[i];
        int present = 0;
        for (size_t j = 0; j < count; ++j) {
            if (values[j] == (int)(i + 1)) {
                present = 1;
                break;
            }
        }
        if (!present) {
            expected[expected_count++] = (int)(i + 1);
        }
    }
    resetAllocator();
    MissingNumbers result;
    assert(findMissingNumbers(values, count, &result) == MISSING_NUMBERS_OK);
    assert(result.count == expected_count);
    assert(allocation_calls == (expected_count == 0 ? 0u : 1u));
    assert(requested_bytes == expected_count * sizeof *result.numbers);
    assert((expected_count == 0) == (result.numbers == NULL));
    for (size_t i = 0; i < count; ++i) {
        assert(original[i] == values[i]);
    }
    for (size_t i = 0; i < expected_count; ++i) {
        assert(result.numbers[i] == expected[i]);
    }
    free(result.numbers);
}

static size_t testSmallArrays(void) {
    checkMissing(NULL, 0);
    int values[6];
    size_t cases = 1;
    for (size_t count = 1; count <= 6; ++count) {
        size_t combinations = 1;
        for (size_t i = 0; i < count; ++i) {
            combinations *= count;
        }
        for (size_t code = 0; code < combinations; ++code) {
            size_t digits = code;
            for (size_t i = 0; i < count; ++i) {
                values[i] = (int)(digits % count + 1);
                digits /= count;
            }
            checkMissing(values, count);
            ++cases;
        }
    }
    return cases;
}

static void testInvalidInput(void) {
    int sentinel = 71;
    MissingNumbers result = {.numbers = &sentinel, .count = 9};
    int values[] = {2, 1, 3};
    resetAllocator();
    assert(findMissingNumbers(values, 3, NULL) == MISSING_NUMBERS_INVALID);
    assert(findMissingNumbers(NULL, 3, &result) == MISSING_NUMBERS_INVALID);
    assert(findMissingNumbers(values, SIZE_MAX, &result) == MISSING_NUMBERS_INVALID);

    const int bad_values[] = {0, -1, INT_MIN, 4};
    for (size_t i = 0; i < sizeof bad_values / sizeof bad_values[0]; ++i) {
        values[2] = bad_values[i];
        assert(findMissingNumbers(values, 3, &result) == MISSING_NUMBERS_INVALID);
        assert(values[0] == 2 && values[1] == 1 && values[2] == bad_values[i]);
        assert(result.numbers == &sentinel && result.count == 9);
    }
    assert(allocation_calls == 0 && requested_bytes == 0);
}

static void testAllocationFailure(void) {
    const int original[] = {4, 2, 7, 7, 8, 2, 3, 1};
    int values[8];
    memcpy(values, original, sizeof values);
    int sentinel = 71;
    MissingNumbers result = {.numbers = &sentinel, .count = 9};
    resetAllocator();
    fail_allocation = 1;
    assert(findMissingNumbers(values, 8, &result) == MISSING_NUMBERS_ALLOCATION_FAILURE);
    assert(allocation_calls == 1 && requested_bytes == 2 * sizeof(int));
    assert(result.numbers == &sentinel && result.count == 9);
    assert(memcmp(original, values, sizeof values) == 0);

    fail_allocation = 0;
    assert(findMissingNumbers(values, 8, &result) == MISSING_NUMBERS_OK);
    assert(result.count == 2 && result.numbers[0] == 5 && result.numbers[1] == 6);
    assert(memcmp(original, values, sizeof values) == 0);
    free(result.numbers);
}

int main(void) {
    size_t cases = testSmallArrays();
    testInvalidInput();
    testAllocationFailure();
    printf("[PASSED] Missing Numbers: %zu oracle cases, validation, exact allocation, and input restoration after success and allocation failure.\n", cases);
    return 0;
}
#endif
