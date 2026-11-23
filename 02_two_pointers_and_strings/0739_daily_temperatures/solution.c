/* Daily Temperatures practice: reuse unfinished answer slots as stack links. */
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef NDEBUG
#error "The standalone harness requires assertions."
#endif

typedef enum {
    TEMPERATURE_OK,
    TEMPERATURE_INVALID,
    TEMPERATURE_NO_MEMORY
} TemperatureStatus;

static TemperatureStatus temperatures_with_allocator(
    const int *values, size_t count, int **out, void *(*allocate)(size_t)) {
    if (!out) return TEMPERATURE_INVALID;
    *out = NULL;
    if (!allocate || count > (size_t)INT_MAX || count > SIZE_MAX / sizeof(int) ||
        (count != 0 && !values)) {
        return TEMPERATURE_INVALID;
    }
    if (count == 0) return TEMPERATURE_OK;

    int *wait = allocate(count * sizeof(*wait));
    if (!wait) return TEMPERATURE_NO_MEMORY;

    /* Zero ends the chain. Other links encode a pending day as its index + 1. */
    int pending = 0;
    for (size_t day = 0; day < count; ++day) {
        while (pending != 0) {
            const size_t previous = (size_t)(pending - 1);
            if (values[day] <= values[previous]) break;
            pending = wait[previous];
            wait[previous] = (int)(day - previous);
        }
        wait[day] = pending;
        pending = (int)(day + 1);
    }
    while (pending != 0) {
        const size_t previous = (size_t)(pending - 1);
        pending = wait[previous];
        wait[previous] = 0;
    }

    *out = wait;
    return TEMPERATURE_OK;
}

/* Borrow values. Transfer the answer to the caller, who releases it with free. */
TemperatureStatus daily_temperatures(const int *values, size_t count, int **out) {
    return temperatures_with_allocator(values, count, out, malloc);
}

static void check_with_oracle(const int *values, size_t count) {
    int *wait = NULL;
    assert(daily_temperatures(values, count, &wait) == TEMPERATURE_OK);
    assert((wait == NULL) == (count == 0));
    for (size_t day = 0; day < count; ++day) {
        size_t later = day + 1;
        while (later < count && values[later] <= values[day]) ++later;
        assert(wait[day] == (later == count ? 0 : (int)(later - day)));
    }
    free(wait);
}

static size_t allocation_calls, requested_bytes;

static void *observe_allocation(size_t bytes) {
    ++allocation_calls;
    requested_bytes = bytes;
    return malloc(bytes);
}

static void *deny_allocation(size_t bytes) {
    ++allocation_calls;
    requested_bytes = bytes;
    return NULL;
}

static void check_allocation_contract(void) {
    const int values[] = {5, 5, INT_MAX};
    int placeholder;
    int *wait = &placeholder;
    assert(temperatures_with_allocator(values, 3, &wait, deny_allocation) ==
           TEMPERATURE_NO_MEMORY);
    assert(wait == NULL && allocation_calls == 1 && requested_bytes == 3 * sizeof(int));

    allocation_calls = 0;
    assert(temperatures_with_allocator(NULL, 0, &wait, deny_allocation) == TEMPERATURE_OK);
    assert(wait == NULL && allocation_calls == 0);
    wait = &placeholder;
    assert(temperatures_with_allocator(NULL, 1, &wait, deny_allocation) == TEMPERATURE_INVALID);
    assert(wait == NULL && allocation_calls == 0);
    assert(temperatures_with_allocator(values, 3, NULL, deny_allocation) == TEMPERATURE_INVALID);
    assert(allocation_calls == 0);
    wait = &placeholder;
    assert(temperatures_with_allocator(values, SIZE_MAX, &wait, deny_allocation) ==
           TEMPERATURE_INVALID);
    assert(wait == NULL && allocation_calls == 0);

    assert(temperatures_with_allocator(values, 3, &wait, observe_allocation) == TEMPERATURE_OK);
    assert(allocation_calls == 1 && requested_bytes == 3 * sizeof(int));
    assert(wait[0] == 2 && wait[1] == 1 && wait[2] == 0);
    free(wait);
}

int main(void) {
    const int symbols[] = {INT_MIN, 0, INT_MAX};
    size_t cases = 0;
    size_t patterns = 1;
    for (size_t count = 0; count <= 7; ++count, patterns *= 3) {
        for (size_t pattern = 0; pattern < patterns; ++pattern) {
            size_t digits = pattern;
            int values[7] = {0};
            for (size_t i = 0; i < count; ++i, digits /= 3) {
                values[i] = symbols[digits % 3];
            }
            int original[7];
            memcpy(original, values, sizeof(values));
            check_with_oracle(values, count);
            assert(memcmp(original, values, sizeof(values)) == 0);
            ++cases;
        }
    }

    enum { LARGE_COUNT = 8192 };
    static int descending[LARGE_COUNT];
    for (size_t i = 0; i < LARGE_COUNT - 1; ++i) descending[i] = LARGE_COUNT - (int)i;
    descending[LARGE_COUNT - 1] = INT_MAX;
    int *wait = NULL;
    assert(daily_temperatures(descending, LARGE_COUNT, &wait) == TEMPERATURE_OK);
    for (size_t i = 0; i < LARGE_COUNT - 1; ++i) {
        assert(wait[i] == (int)(LARGE_COUNT - 1 - i));
        assert(descending[i] == LARGE_COUNT - (int)i);
    }
    assert(wait[LARGE_COUNT - 1] == 0 && descending[LARGE_COUNT - 1] == INT_MAX);
    free(wait);

    check_allocation_contract();
    assert(cases == 3280);
    printf("[PASSED] Daily Temperatures: %zu oracle cases, 8192-day stack stress, allocation and input checks.\n", cases);
    return 0;
}
