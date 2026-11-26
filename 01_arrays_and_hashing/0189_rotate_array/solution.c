#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static void reverseRange(int *values, size_t first, size_t end) {
    while (end - first > 1) {
        --end;
        int saved = values[first];
        values[first] = values[end];
        values[end] = saved;
        ++first;
    }
}

/* Nonempty input must name count writable ints. Empty input is a no-op. */
bool rotateRight(int *values, size_t count, size_t steps) {
    if (count == 0) {
        return true;
    }
    if (values == NULL || count > SIZE_MAX / sizeof *values) {
        return false;
    }

    size_t remainder = steps % count;
    if (remainder != 0) {
        reverseRange(values, 0, count);
        reverseRange(values, 0, remainder);
        reverseRange(values, remainder, count);
    }
    return true;
}

#ifndef ROTATE_ARRAY_NO_TEST_MAIN
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

static void checkRotation(const int *input, size_t count, size_t steps) {
    int actual[6];
    int expected[6];
    assert(count <= sizeof actual / sizeof actual[0]);
    if (count == 0) {
        assert(rotateRight(NULL, 0, steps));
        return;
    }

    memcpy(actual, input, count * sizeof *actual);
    size_t shift = steps % count;
    for (size_t i = 0; i < count; ++i) {
        expected[(i + shift) % count] = input[i];
    }
    assert(rotateRight(actual, count, steps));
    for (size_t i = 0; i < count; ++i) {
        assert(actual[i] == expected[i]);
    }
}

static size_t testSmallInputs(void) {
    const int alphabet[] = {INT_MIN, 0, INT_MAX};
    int input[6];
    size_t cases = 0;
    for (size_t n = 0; n <= sizeof input / sizeof input[0]; ++n) {
        size_t arrangements = 1;
        for (size_t i = 0; i < n; ++i) {
            arrangements *= 3;
        }
        for (size_t code = 0; code < arrangements; ++code) {
            size_t digits = code;
            for (size_t i = 0; i < n; ++i) {
                input[i] = alphabet[digits % 3];
                digits /= 3;
            }
            for (size_t steps = 0; steps <= 2 * n; ++steps) {
                checkRotation(input, n, steps);
                ++cases;
            }
            checkRotation(input, n, SIZE_MAX);
            ++cases;
        }
    }
    return cases;
}

static void testBoundaries(void) {
    int values[] = {80, 1, 2, 3, 4, 5, 90};
    const int expected[] = {80, 4, 5, 1, 2, 3, 90};

    assert(rotateRight(values + 1, 5, 7));
    for (size_t i = 0; i < sizeof values / sizeof values[0]; ++i) {
        assert(values[i] == expected[i]);
    }
    assert(!rotateRight(NULL, 1, 2));
    if (sizeof *values > 1) {
        assert(!rotateRight(values, SIZE_MAX / sizeof *values + 1, 2));
        assert(values[0] == 80);
    }
}

int main(void) {
    size_t cases = testSmallInputs();
    testBoundaries();
    printf("[PASSED] Rotate Array: %zu oracle cases, guarded subrange and invalid inputs.\n", cases);
    return 0;
}
#endif
