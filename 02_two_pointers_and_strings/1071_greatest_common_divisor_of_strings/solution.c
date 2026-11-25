#include <stdbool.h>
#include <stddef.h>

typedef struct {
    const char *data;
    size_t length;
} StringDivisor;

static size_t gcdLength(size_t first, size_t second) {
    while (second != 0) {
        size_t remainder = first % second;
        first = second;
        second = remainder;
    }
    return first;
}

static bool repeatsPrefix(const char *bytes, size_t length,
                          const char *prefix, size_t prefix_length) {
    size_t offset = 0;
    for (size_t i = 0; i < length; ++i) {
        if (bytes[i] != prefix[offset]) {
            return false;
        }
        if (++offset == prefix_length) {
            offset = 0;
        }
    }
    return true;
}

/*
 * Both nonempty spans must be readable and result must be disjoint from them.
 * A match borrows the first span. Valid inputs with no match return {NULL, 0}.
 * Invalid arguments leave result unchanged.
 */
bool gcdStringView(const char *first, size_t first_len, const char *second,
                   size_t second_len, StringDivisor *result) {
    if (first == NULL || second == NULL || first_len == 0 ||
        second_len == 0 || result == NULL) {
        return false;
    }

    size_t length = gcdLength(first_len, second_len);
    bool matches = repeatsPrefix(first + length, first_len - length, first, length)
                && repeatsPrefix(second, second_len, first, length);
    *result = matches ? (StringDivisor){first, length} : (StringDivisor){NULL, 0};
    return true;
}

#ifndef GCD_STRING_NO_TEST_MAIN
#include <assert.h>
#include <stdio.h>

static size_t expectedDivisor(const char *a, size_t n, const char *b, size_t m) {
    size_t limit = n < m ? n : m;
    for (size_t size = limit; size > 0; --size) {
        if (n % size != 0 || m % size != 0) {
            continue;
        }
        bool match = true;
        for (size_t i = 0; i < n; ++i) {
            if (a[i] != a[i % size]) {
                match = false;
                break;
            }
        }
        for (size_t i = 0; match && i < m; ++i) {
            if (b[i] != a[i % size]) {
                match = false;
                break;
            }
        }
        if (match) {
            return size;
        }
    }
    return 0;
}

static void fillBinary(char *bytes, size_t length, unsigned bits) {
    for (size_t i = 0; i < length; ++i) {
        bytes[i] = (bits & (1u << i)) ? 'A' : 'B';
    }
}

static size_t testSmallPairs(void) {
    char a[6];
    char b[6];
    size_t cases = 0;
    for (size_t n = 1; n <= sizeof a; ++n) {
        for (unsigned x = 0; x < (1u << n); ++x) {
            fillBinary(a, n, x);
            for (size_t m = 1; m <= sizeof b; ++m) {
                for (unsigned y = 0; y < (1u << m); ++y) {
                    fillBinary(b, m, y);
                    size_t expected = expectedDivisor(a, n, b, m);
                    StringDivisor result;
                    assert(gcdStringView(a, n, b, m, &result));
                    assert(result.length == expected);
                    assert(result.data == (expected == 0 ? NULL : a));
                    ++cases;
                }
            }
        }
    }
    return cases;
}

static void testBoundaries(void) {
    const char a[] = {'A', '\0', 'A', '\0'};
    const char b[] = {'A', '\0', 'A', '\0', 'A', '\0'};
    const char mismatch[] = {'A', '\0', 'A', '\0', 'A', 'B'};
    StringDivisor result;
    assert(gcdStringView(a, sizeof a, b, sizeof b, &result));
    assert(result.data == a && result.length == 2);
    assert(gcdStringView(a, sizeof a, a + 2, 2, &result));
    assert(result.data == a && result.length == 2);
    assert(gcdStringView(a, sizeof a, mismatch, sizeof mismatch, &result));
    assert(result.data == NULL && result.length == 0);
    assert(gcdStringView(a, sizeof a, a, sizeof a, &result));
    assert(result.data == a && result.length == sizeof a);

    assert(!gcdStringView(NULL, sizeof a, b, sizeof b, &result));
    assert(!gcdStringView(a, sizeof a, NULL, sizeof b, &result));
    assert(!gcdStringView(a, 0, b, sizeof b, &result));
    assert(!gcdStringView(a, sizeof a, b, 0, &result));
    assert(!gcdStringView(a, sizeof a, b, sizeof b, NULL));
    assert(result.data == a && result.length == sizeof a);
}

int main(void) {
    size_t cases = testSmallPairs();
    testBoundaries();
    printf("[PASSED] GCD of Strings: %zu oracle pairs, byte-span boundaries, and borrowed results.\n", cases);
    return 0;
}
#endif
