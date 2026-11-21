/* Separately labelled checked practice; not the historical Accepted source. */
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef NDEBUG
#error "The standalone practice harness requires assertions."
#endif

enum { BEAUTIFUL_ARRAY_MAX_N = 1000 };

typedef enum {
    BEAUTIFUL_ARRAY_OK,
    BEAUTIFUL_ARRAY_INVALID_ARGUMENT,
    BEAUTIFUL_ARRAY_NO_MEMORY
} BeautifulArrayStatus;

typedef void* (*Allocate)(size_t);
typedef void (*Release)(void*);

/* Private test seam; the public wrapper below always uses malloc and free. */
static BeautifulArrayStatus beautiful_array_with_allocator(
    int n, int** out_values, int* out_size, Allocate allocate, Release release) {
    if (out_values != NULL) *out_values = NULL;
    if (out_size != NULL) *out_size = 0;
    if (out_values == NULL || out_size == NULL || allocate == NULL ||
        release == NULL || n < 1 || n > BEAUTIFUL_ARRAY_MAX_N ||
        (size_t)n > SIZE_MAX / sizeof(int)) {
        return BEAUTIFUL_ARRAY_INVALID_ARGUMENT;
    }

    const size_t bytes = (size_t)n * sizeof(int);
    int* result = allocate(bytes);
    if (result == NULL) return BEAUTIFUL_ARRAY_NO_MEMORY;
    int* temporary = allocate(bytes);
    if (temporary == NULL) {
        release(result);
        return BEAUTIFUL_ARRAY_NO_MEMORY;
    }

    result[0] = 1;
    int count = 1;
    while (count < n) {
        int written = 0;
        for (int i = 0; i < count; ++i) {
            const int odd = result[i] * 2 - 1;
            if (odd <= n) temporary[written++] = odd;
        }
        for (int i = 0; i < count; ++i) {
            const int even = result[i] * 2;
            if (even <= n) temporary[written++] = even;
        }
        for (int i = 0; i < written; ++i) result[i] = temporary[i];
        count = written;
    }

    release(temporary);
    *out_values = result;
    *out_size = n;
    return BEAUTIFUL_ARRAY_OK;
}

/* Output slots are for a fresh result; caller frees a successful array once. */
BeautifulArrayStatus beautiful_array_checked(int n, int** out_values,
                                            int* out_size) {
    return beautiful_array_with_allocator(n, out_values, out_size, malloc, free);
}

/* ======================================================================= */
/* Standalone synthetic harness; no external input or source modification.   */
/* ======================================================================= */

enum { TRACKED_SLOTS = 4 };
struct TrackedBlock {
    void* pointer;
    size_t bytes;
};

static struct TrackedBlock tracked[TRACKED_SLOTS];
static size_t allocation_attempts;
static size_t fail_at;
static size_t live_blocks;
static size_t live_bytes;
static size_t peak_bytes;
static size_t release_calls;

static void tracker_reset(size_t failure_position) {
    assert(live_blocks == 0 && live_bytes == 0);
    for (size_t i = 0; i < TRACKED_SLOTS; ++i) {
        assert(tracked[i].pointer == NULL && tracked[i].bytes == 0);
    }
    allocation_attempts = 0;
    fail_at = failure_position;
    peak_bytes = 0;
    release_calls = 0;
}

static void* tracked_allocate(size_t bytes) {
    ++allocation_attempts;
    if (fail_at != 0 && allocation_attempts == fail_at) return NULL;
    assert(bytes != 0 && bytes <= SIZE_MAX - live_bytes);
    void* pointer = malloc(bytes);
    assert(pointer != NULL); /* Host OOM makes the test fail, not silently pass. */
    size_t slot = 0;
    while (slot < TRACKED_SLOTS && tracked[slot].pointer != NULL) ++slot;
    assert(slot < TRACKED_SLOTS);
    tracked[slot] = (struct TrackedBlock){pointer, bytes};
    ++live_blocks;
    live_bytes += bytes;
    if (live_bytes > peak_bytes) peak_bytes = live_bytes;
    return pointer;
}

static void tracked_release(void* pointer) {
    if (pointer == NULL) return;
    size_t slot = 0;
    while (slot < TRACKED_SLOTS && tracked[slot].pointer != pointer) ++slot;
    assert(slot < TRACKED_SLOTS); /* Reject unknown and duplicate releases. */
    const size_t bytes = tracked[slot].bytes;
    tracked[slot] = (struct TrackedBlock){NULL, 0};
    assert(live_blocks != 0 && live_bytes >= bytes);
    --live_blocks;
    live_bytes -= bytes;
    ++release_calls;
    free(pointer);
}

static void reclaim_baseline_fixture(void) {
    for (size_t i = 0; i < TRACKED_SLOTS; ++i) {
        if (tracked[i].pointer != NULL) tracked_release(tracked[i].pointer);
    }
    assert(live_blocks == 0 && live_bytes == 0);
}

/* stdlib is already included. Macros affect only this unchanged test include. */
#define beautifulArray historical_beautiful_array
#define malloc tracked_allocate
#define free tracked_release
/* Preserve the archive's missing final newline; suppress only its Clang warning. */
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnewline-eof"
#endif
#include "../../leetcode/accepted/0932_beautiful_array/submission.c"
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
#undef free
#undef malloc
#undef beautifulArray

/* Independent of odd/even construction: test the defining midpoint property. */
static void assert_beautiful(const int* values, int n) {
    assert(values != NULL && n >= 1 && n <= BEAUTIFUL_ARRAY_MAX_N);
    int position[BEAUTIFUL_ARRAY_MAX_N + 1];
    for (int value = 0; value <= n; ++value) position[value] = -1;
    for (int i = 0; i < n; ++i) {
        assert(values[i] >= 1 && values[i] <= n);
        assert(position[values[i]] == -1);
        position[values[i]] = i;
    }
    for (int value = 1; value <= n; ++value) assert(position[value] >= 0);
    for (int low = 1; low <= n; ++low) {
        for (int high = low + 2; high <= n; high += 2) {
            const int middle = (low + high) / 2;
            const int a = position[low], b = position[high];
            const int left = a < b ? a : b, right = a < b ? b : a;
            assert(!(left < position[middle] && position[middle] < right));
        }
    }
}

static size_t test_all_supported_sizes(void) {
    size_t cases = 0;
    for (int n = 1; n <= BEAUTIFUL_ARRAY_MAX_N; ++n) {
        int* values = NULL;
        int size = -1;
        assert(beautiful_array_checked(n, &values, &size) == BEAUTIFUL_ARRAY_OK);
        assert(size == n);
        assert_beautiful(values, n);
        free(values);
        ++cases;
    }
    return cases;
}

static size_t test_allocation_failures(void) {
    size_t cases = 0;
    for (int n = 1; n <= BEAUTIFUL_ARRAY_MAX_N; ++n) {
        for (size_t failure = 1; failure <= 2; ++failure) {
            tracker_reset(failure);
            int sentinel = 0;
            int* values = &sentinel;
            int size = -1;
            assert(beautiful_array_with_allocator(n, &values, &size,
                       tracked_allocate, tracked_release) == BEAUTIFUL_ARRAY_NO_MEMORY);
            assert(values == NULL && size == 0);
            assert(allocation_attempts == failure);
            assert(release_calls == failure - 1);
            assert(live_blocks == 0 && live_bytes == 0);
            ++cases;
        }
    }
    return cases;
}

static void test_invalid_call(int n, unsigned missing_outputs, bool use_tracker) {
    tracker_reset(0);
    int sentinel = 0;
    int* values = &sentinel;
    int size = -1;
    int** values_slot = (missing_outputs & 1U) != 0 ? NULL : &values;
    int* size_slot = (missing_outputs & 2U) != 0 ? NULL : &size;
    const BeautifulArrayStatus status = use_tracker
        ? beautiful_array_with_allocator(n, values_slot, size_slot,
                                         tracked_allocate, tracked_release)
        : beautiful_array_checked(n, values_slot, size_slot);
    assert(status == BEAUTIFUL_ARRAY_INVALID_ARGUMENT);
    if (values_slot != NULL) assert(values == NULL);
    if (size_slot != NULL) assert(size == 0);
    assert(allocation_attempts == 0 && live_blocks == 0 && live_bytes == 0);
}

static size_t test_invalid_arguments(void) {
    const int invalid_sizes[] = {INT_MIN, -1, 0, 1001, INT_MAX};
    size_t cases = 0;
    for (unsigned use_tracker = 0; use_tracker < 2; ++use_tracker) {
        for (size_t i = 0; i < sizeof(invalid_sizes) / sizeof(invalid_sizes[0]); ++i) {
            test_invalid_call(invalid_sizes[i], 0, use_tracker != 0);
            ++cases;
        }
        for (unsigned missing = 1; missing <= 3; ++missing) {
            test_invalid_call(8, missing, use_tracker != 0);
            ++cases;
        }
    }
    for (unsigned missing = 0; missing < 2; ++missing) {
        tracker_reset(0);
        int sentinel = 0;
        int* values = &sentinel;
        int size = -1;
        assert(beautiful_array_with_allocator(8, &values, &size,
                   missing == 0 ? NULL : tracked_allocate,
                   missing == 1 ? NULL : tracked_release)
               == BEAUTIFUL_ARRAY_INVALID_ARGUMENT);
        assert(values == NULL && size == 0);
        assert(allocation_attempts == 0 && live_blocks == 0 && live_bytes == 0);
        ++cases;
    }
    return cases;
}

static void test_checked_allocation_control(void) {
    tracker_reset(0);
    int* values = NULL;
    int size = -1;
    assert(beautiful_array_with_allocator(8, &values, &size,
               tracked_allocate, tracked_release) == BEAUTIFUL_ARRAY_OK);
    assert(size == 8 && allocation_attempts == 2 && release_calls == 1);
    assert(live_blocks == 1 && live_bytes == 8 * sizeof(int));
    assert(peak_bytes == 16 * sizeof(int));
    assert_beautiful(values, size);
    tracked_release(values);
    assert(live_blocks == 0 && live_bytes == 0);
}

static void test_historical_controls(void) {
    for (size_t failure = 1; failure <= 2; ++failure) {
        tracker_reset(failure);
        int size = -1;
        int* values = historical_beautiful_array(8, &size);
        assert(values == NULL && size == 8 && allocation_attempts == 2);
        assert(live_blocks == 1 && live_bytes == 8 * sizeof(int));
        printf("[OBSERVED] Beautiful Array original failure %zu: "
               "%zu requested bytes retained at return; checked path retains 0.\n",
               failure, live_bytes);
        /* The unchanged source cannot reach this block; the test registry can. */
        reclaim_baseline_fixture();
    }
    tracker_reset(0);
    int size = -1;
    int* values = historical_beautiful_array(8, &size);
    assert(size == 8 && allocation_attempts == 2 && release_calls == 1);
    assert(live_blocks == 1 && live_bytes == 8 * sizeof(int));
    assert_beautiful(values, size);
    tracked_release(values);
    assert(live_blocks == 0 && live_bytes == 0);
}

int main(void) {
    printf("[TEST] Beautiful Array checked practice; sizeof(int)=%zu.\n", sizeof(int));
    const size_t properties = test_all_supported_sizes();
    const size_t failures = test_allocation_failures();
    const size_t invalid = test_invalid_arguments();
    test_checked_allocation_control();
    test_historical_controls();
    assert(properties == 1000 && failures == 2000 && invalid == 18);
    assert(live_blocks == 0 && live_bytes == 0);
    printf("[PASSED] Beautiful Array checked practice: %zu property cases, "
           "%zu allocation failures, %zu invalid arguments, 1 checked allocation "
           "control, 2 historical failure cases, 1 historical success control; "
           "zero tracked blocks after fixture cleanup.\n\n",
           properties, failures, invalid);
    return 0;
}
