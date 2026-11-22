/* Checked Course Schedule practice; historical Accepted source is separate. */
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef NDEBUG
#error "The standalone harness requires assertions."
#endif

typedef struct {
    int dependent;
    int prerequisite;
} CoursePrerequisite;

typedef enum {
    COURSE_SCHEDULE_POSSIBLE,
    COURSE_SCHEDULE_CYCLE,
    COURSE_SCHEDULE_INVALID_ARGUMENT,
    COURSE_SCHEDULE_NO_MEMORY
} CourseScheduleStatus;

typedef void* (*Allocate)(size_t);
typedef void (*Release)(void*);

typedef struct {
    size_t input_bytes;
    size_t offsets_bytes;
    size_t targets_bytes;
    size_t vector_bytes;
} CourseGraphStorage;

/* Optional private observations count actual CSR traversal, not fast paths. */
typedef struct {
    bool used_csr;
    size_t initial_ready;
    size_t processed;
    size_t enqueued;
    size_t max_ready;
} CourseScheduleStats;

static bool checked_add_size(size_t a, size_t b, size_t* result) {
    if (a > SIZE_MAX - b) return false;
    *result = a + b;
    return true;
}

static bool checked_multiply_size(size_t a, size_t b, size_t* result) {
    if (b != 0 && a > SIZE_MAX / b) return false;
    *result = a * b;
    return true;
}

static bool course_graph_storage(size_t vertices, size_t edges,
                                 CourseGraphStorage* storage) {
    size_t offset_count;
    if (vertices > (size_t)INT_MAX ||
        !checked_add_size(vertices, 1, &offset_count) ||
        !checked_multiply_size(edges, sizeof(CoursePrerequisite),
                               &storage->input_bytes) ||
        !checked_multiply_size(offset_count, sizeof(size_t),
                               &storage->offsets_bytes) ||
        !checked_multiply_size(edges, sizeof(int), &storage->targets_bytes) ||
        !checked_multiply_size(vertices, sizeof(size_t), &storage->vector_bytes)) {
        return false;
    }
    return true;
}

/* Borrowed pairs must remain accessible and unchanged throughout the call. */
static CourseScheduleStatus course_schedule_with_allocator(
    size_t vertices, const CoursePrerequisite* pairs, size_t edges,
    Allocate allocate, Release release, CourseScheduleStats* stats) {
    if (stats != NULL) *stats = (CourseScheduleStats){false, 0, 0, 0, 0};
    CourseGraphStorage storage;
    if (allocate == NULL || release == NULL ||
        !course_graph_storage(vertices, edges, &storage) ||
        (edges != 0 && (pairs == NULL || vertices == 0))) {
        return COURSE_SCHEDULE_INVALID_ARGUMENT;
    }
    /* An edgeless graph needs neither queue storage nor zero-size allocation. */
    if (edges == 0) return COURSE_SCHEDULE_POSSIBLE;

    /* Size/extent checks above precede every access to the input pair buffer. */
    for (size_t i = 0; i < edges; ++i) {
        if (pairs[i].dependent < 0 || pairs[i].prerequisite < 0 ||
            (size_t)pairs[i].dependent >= vertices ||
            (size_t)pairs[i].prerequisite >= vertices) {
            return COURSE_SCHEDULE_INVALID_ARGUMENT;
        }
    }

    size_t* offsets = NULL;
    int* targets = NULL;
    size_t* indegree = NULL;
    size_t* work = NULL;
    CourseScheduleStatus status = COURSE_SCHEDULE_NO_MEMORY;
    offsets = allocate(storage.offsets_bytes);
    if (offsets == NULL) goto cleanup;
    targets = allocate(storage.targets_bytes);
    if (targets == NULL) goto cleanup;
    indegree = allocate(storage.vector_bytes);
    if (indegree == NULL) goto cleanup;
    work = allocate(storage.vector_bytes);
    if (work == NULL) goto cleanup;

    for (size_t i = 0; i <= vertices; ++i) offsets[i] = 0;
    for (size_t i = 0; i < vertices; ++i) indegree[i] = 0;
    for (size_t i = 0; i < edges; ++i) {
        ++offsets[(size_t)pairs[i].prerequisite + 1];
        ++indegree[(size_t)pairs[i].dependent];
    }
    /* These sums are bounded by the validated, representable edge count. */
    for (size_t i = 1; i <= vertices; ++i) offsets[i] += offsets[i - 1];
    assert(offsets[vertices] == edges);
    for (size_t i = 0; i < vertices; ++i) work[i] = offsets[i];
    for (size_t i = 0; i < edges; ++i) {
        const size_t prerequisite = (size_t)pairs[i].prerequisite;
        assert(work[prerequisite] < offsets[prerequisite + 1]);
        targets[work[prerequisite]++] = pairs[i].dependent;
    }

    /* CSR build cursors are finished; the same V entries become a ready queue. */
    size_t head = 0, tail = 0, processed = 0;
    for (size_t i = 0; i < vertices; ++i) {
        if (indegree[i] == 0) work[tail++] = i;
    }
    if (stats != NULL) {
        stats->used_csr = true;
        stats->initial_ready = tail;
        stats->max_ready = tail;
    }
    while (head < tail) {
        const size_t vertex = work[head++];
        ++processed;
        for (size_t i = offsets[vertex]; i < offsets[vertex + 1]; ++i) {
            const size_t dependent = (size_t)targets[i];
            assert(indegree[dependent] != 0);
            --indegree[dependent];
            if (indegree[dependent] == 0) {
                assert(tail < vertices);
                work[tail++] = dependent;
            }
        }
        if (stats != NULL && tail - head > stats->max_ready) {
            stats->max_ready = tail - head;
        }
    }
    if (stats != NULL) {
        stats->processed = processed;
        stats->enqueued = tail;
    }
    status = processed == vertices ? COURSE_SCHEDULE_POSSIBLE : COURSE_SCHEDULE_CYCLE;

cleanup:
    if (work != NULL) release(work);
    if (indegree != NULL) release(indegree);
    if (targets != NULL) release(targets);
    if (offsets != NULL) release(offsets);
    return status;
}

/* V <= INT_MAX; empty graph is possible; duplicate edges keep multiplicity. */
CourseScheduleStatus course_schedule_checked(
    size_t vertices, const CoursePrerequisite* pairs, size_t edges) {
    return course_schedule_with_allocator(vertices, pairs, edges, malloc, free, NULL);
}

/* ======================================================================= */
/* Standalone synthetic tests. No historical archived implementation runs.   */
/* ======================================================================= */

enum { TRACKED_SLOTS = 4, SMALL_VERTICES = 3, SMALL_EDGE_SLOTS = 9 };
struct TrackedBlock {
    void* pointer;
    size_t bytes;
};
static struct TrackedBlock tracked[TRACKED_SLOTS];
static size_t attempts, fail_at, live_blocks, live_bytes, peak_bytes, releases;
static size_t requested_bytes[TRACKED_SLOTS];

static void tracker_reset(size_t failure_position) {
    assert(live_blocks == 0 && live_bytes == 0);
    for (size_t i = 0; i < TRACKED_SLOTS; ++i) {
        assert(tracked[i].pointer == NULL && tracked[i].bytes == 0);
        requested_bytes[i] = 0;
    }
    attempts = 0;
    fail_at = failure_position;
    peak_bytes = 0;
    releases = 0;
}

static void* tracked_allocate(size_t bytes) {
    assert(attempts < TRACKED_SLOTS && bytes != 0);
    requested_bytes[attempts++] = bytes;
    if (fail_at != 0 && attempts == fail_at) return NULL;
    assert(bytes <= SIZE_MAX - live_bytes);
    void* pointer = malloc(bytes);
    assert(pointer != NULL);
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
    assert(pointer != NULL);
    size_t slot = 0;
    while (slot < TRACKED_SLOTS && tracked[slot].pointer != pointer) ++slot;
    assert(slot < TRACKED_SLOTS);
    const size_t bytes = tracked[slot].bytes;
    tracked[slot] = (struct TrackedBlock){NULL, 0};
    assert(live_blocks != 0 && live_bytes >= bytes);
    --live_blocks;
    live_bytes -= bytes;
    ++releases;
    free(pointer);
}

static CourseScheduleStatus reachability_oracle(const CoursePrerequisite* pairs,
                                               size_t edges) {
    bool reachable[SMALL_VERTICES][SMALL_VERTICES] = {{false}};
    for (size_t i = 0; i < edges; ++i) {
        reachable[pairs[i].prerequisite][pairs[i].dependent] = true;
    }
    for (size_t through = 0; through < SMALL_VERTICES; ++through) {
        for (size_t from = 0; from < SMALL_VERTICES; ++from) {
            for (size_t to = 0; to < SMALL_VERTICES; ++to) {
                if (reachable[from][through] && reachable[through][to]) {
                    reachable[from][to] = true;
                }
            }
        }
    }
    for (size_t i = 0; i < SMALL_VERTICES; ++i) {
        if (reachable[i][i]) return COURSE_SCHEDULE_CYCLE;
    }
    return COURSE_SCHEDULE_POSSIBLE;
}

static size_t test_exhaustive_graphs(size_t* failure_cases) {
    size_t cases = 0;
    *failure_cases = 0;
    for (unsigned mask = 0; mask < (1U << SMALL_EDGE_SLOTS); ++mask) {
        CoursePrerequisite pairs[SMALL_EDGE_SLOTS];
        size_t edges = 0;
        for (unsigned prerequisite = 0; prerequisite < SMALL_VERTICES; ++prerequisite) {
            for (unsigned dependent = 0; dependent < SMALL_VERTICES; ++dependent) {
                const unsigned bit = prerequisite * SMALL_VERTICES + dependent;
                if ((mask & (1U << bit)) != 0) {
                    pairs[edges++] = (CoursePrerequisite){(int)dependent, (int)prerequisite};
                }
            }
        }
        const CourseScheduleStatus expected = reachability_oracle(pairs, edges);
        assert(course_schedule_checked(SMALL_VERTICES, pairs, edges) == expected);
        ++cases;
        if (edges == 0) continue;
        for (size_t failure = 1; failure <= 4; ++failure) {
            tracker_reset(failure);
            CourseScheduleStats stats;
            assert(course_schedule_with_allocator(SMALL_VERTICES, pairs, edges,
                       tracked_allocate, tracked_release, &stats) == COURSE_SCHEDULE_NO_MEMORY);
            assert(attempts == failure && releases == failure - 1);
            assert(live_blocks == 0 && live_bytes == 0 && !stats.used_csr);
            ++*failure_cases;
        }
    }
    return cases;
}

static size_t test_fixed_graphs(void) {
    const CoursePrerequisite edge[] = {{1, 0}};
    const CoursePrerequisite cycle[] = {{1, 0}, {0, 1}};
    const CoursePrerequisite self[] = {{0, 0}};
    const CoursePrerequisite chain[] = {{1, 0}, {2, 1}};
    const CoursePrerequisite disconnected[] = {{1, 0}, {3, 2}};
    const CoursePrerequisite disconnected_cycle[] = {{1, 0}, {0, 1}, {3, 2}};
    const CoursePrerequisite duplicate[] = {{1, 0}, {1, 0}, {2, 1}};
    const CoursePrerequisite duplicate_cycle[] = {{1, 0}, {1, 0}, {0, 1}};
    const CoursePrerequisite diamond[] = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    assert(course_schedule_checked(0, NULL, 0) == COURSE_SCHEDULE_POSSIBLE);
    assert(course_schedule_checked(1, NULL, 0) == COURSE_SCHEDULE_POSSIBLE);
    assert(course_schedule_checked(6, edge, 0) == COURSE_SCHEDULE_POSSIBLE);
    assert(course_schedule_checked(2, edge, 1) == COURSE_SCHEDULE_POSSIBLE);
    assert(course_schedule_checked(2, cycle, 2) == COURSE_SCHEDULE_CYCLE);
    assert(course_schedule_checked(1, self, 1) == COURSE_SCHEDULE_CYCLE);
    assert(course_schedule_checked(3, chain, 2) == COURSE_SCHEDULE_POSSIBLE);
    assert(course_schedule_checked(4, disconnected, 2) == COURSE_SCHEDULE_POSSIBLE);
    assert(course_schedule_checked(4, disconnected_cycle, 3) == COURSE_SCHEDULE_CYCLE);
    assert(course_schedule_checked(3, duplicate, 3) == COURSE_SCHEDULE_POSSIBLE);
    assert(course_schedule_checked(2, duplicate_cycle, 3) == COURSE_SCHEDULE_CYCLE);
    assert(course_schedule_checked(4, diamond, 4) == COURSE_SCHEDULE_POSSIBLE);
    return 12;
}

static size_t test_invalid_arguments(void) {
    const CoursePrerequisite valid[] = {{1, 0}};
    const CoursePrerequisite invalid[] = {{-1, 0}, {0, -1}, {3, 0}, {0, 3}};
    const CoursePrerequisite late_invalid[] = {{1, 0}, {0, 3}};
    const size_t impossible_edges = SIZE_MAX / sizeof(CoursePrerequisite) + 1;
    size_t cases = 0;
    tracker_reset(1);
    assert(course_schedule_with_allocator(3, NULL, 1, tracked_allocate,
               tracked_release, NULL) == COURSE_SCHEDULE_INVALID_ARGUMENT);
    ++cases;
    assert(course_schedule_with_allocator(0, valid, 1, tracked_allocate,
               tracked_release, NULL) == COURSE_SCHEDULE_INVALID_ARGUMENT);
    ++cases;
    assert(course_schedule_with_allocator(3, valid, impossible_edges, tracked_allocate,
               tracked_release, NULL) == COURSE_SCHEDULE_INVALID_ARGUMENT);
    ++cases;
    for (size_t i = 0; i < sizeof(invalid) / sizeof(invalid[0]); ++i) {
        assert(course_schedule_with_allocator(3, &invalid[i], 1, tracked_allocate,
                   tracked_release, NULL) == COURSE_SCHEDULE_INVALID_ARGUMENT);
        ++cases;
    }
    assert(course_schedule_with_allocator(3, late_invalid, 2, tracked_allocate,
               tracked_release, NULL) == COURSE_SCHEDULE_INVALID_ARGUMENT);
    ++cases;
    if ((uintmax_t)SIZE_MAX > (uintmax_t)INT_MAX) {
        assert(course_schedule_with_allocator((size_t)INT_MAX + 1, NULL, 0,
                   tracked_allocate, tracked_release, NULL) == COURSE_SCHEDULE_INVALID_ARGUMENT);
        ++cases;
    }
    assert(course_schedule_with_allocator(2, valid, 1, NULL,
               tracked_release, NULL) == COURSE_SCHEDULE_INVALID_ARGUMENT);
    ++cases;
    assert(course_schedule_with_allocator(2, valid, 1, tracked_allocate,
               NULL, NULL) == COURSE_SCHEDULE_INVALID_ARGUMENT);
    ++cases;
    assert(attempts == 0 && releases == 0 && live_blocks == 0 && live_bytes == 0);
    return cases;
}

static size_t test_checked_arithmetic(void) {
    size_t value = 7, checks = 0;
#define ARITHMETIC_CHECK(condition) do { assert(condition); ++checks; } while (0)
    ARITHMETIC_CHECK(checked_add_size(0, 0, &value) && value == 0);
    ARITHMETIC_CHECK(checked_add_size(SIZE_MAX, 0, &value) && value == SIZE_MAX);
    ARITHMETIC_CHECK(!checked_add_size(SIZE_MAX, 1, &value) && value == SIZE_MAX);
    ARITHMETIC_CHECK(checked_add_size(SIZE_MAX - 1, 1, &value) && value == SIZE_MAX);
    ARITHMETIC_CHECK(checked_multiply_size(0, SIZE_MAX, &value) && value == 0);
    ARITHMETIC_CHECK(checked_multiply_size(SIZE_MAX, 0, &value) && value == 0);
    ARITHMETIC_CHECK(checked_multiply_size(SIZE_MAX, 1, &value) && value == SIZE_MAX);
    ARITHMETIC_CHECK(!checked_multiply_size(SIZE_MAX, 2, &value) && value == SIZE_MAX);
    ARITHMETIC_CHECK(checked_multiply_size(SIZE_MAX / 2, 2, &value)
                     && value == (SIZE_MAX / 2) * 2);
    ARITHMETIC_CHECK(!checked_multiply_size(SIZE_MAX / 2 + 1, 2, &value));
    CourseGraphStorage storage;
    ARITHMETIC_CHECK(course_graph_storage(3, 1, &storage)
                     && storage.input_bytes == sizeof(CoursePrerequisite)
                     && storage.offsets_bytes == 4 * sizeof(size_t)
                     && storage.targets_bytes == sizeof(int)
                     && storage.vector_bytes == 3 * sizeof(size_t));
    ARITHMETIC_CHECK(!course_graph_storage(3,
                     SIZE_MAX / sizeof(CoursePrerequisite) + 1, &storage));
#undef ARITHMETIC_CHECK
    return checks;
}

static void test_allocator_controls(void) {
    const CoursePrerequisite dag[] = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    const CoursePrerequisite cycle[] = {{1, 0}, {0, 1}};
    for (size_t which = 0; which < 2; ++which) {
        tracker_reset(0);
        const CoursePrerequisite* pairs = which == 0 ? dag : cycle;
        const size_t edges = which == 0 ? 4 : 2;
        const CourseScheduleStatus expected = which == 0
            ? COURSE_SCHEDULE_POSSIBLE : COURSE_SCHEDULE_CYCLE;
        CourseScheduleStats stats;
        assert(course_schedule_with_allocator(4, pairs, edges, tracked_allocate,
                   tracked_release, &stats) == expected);
        assert(stats.used_csr && attempts == 4 && releases == 4);
        assert(requested_bytes[0] == 5 * sizeof(size_t));
        assert(requested_bytes[1] == edges * sizeof(int));
        assert(requested_bytes[2] == 4 * sizeof(size_t));
        assert(requested_bytes[3] == 4 * sizeof(size_t));
        assert(peak_bytes == 13 * sizeof(size_t) + edges * sizeof(int));
        assert(live_blocks == 0 && live_bytes == 0);
    }
    tracker_reset(1);
    CourseScheduleStats stats;
    assert(course_schedule_with_allocator(3002, NULL, 0, tracked_allocate,
               tracked_release, &stats) == COURSE_SCHEDULE_POSSIBLE);
    assert(!stats.used_csr && attempts == 0 && releases == 0);
}

static void test_wide_ready_queue(void) {
    const size_t vertices = 3002;
    const CoursePrerequisite edge[] = {{1, 0}};
    assert(course_schedule_checked(vertices, edge, 1) == COURSE_SCHEDULE_POSSIBLE);
    tracker_reset(0);
    CourseScheduleStats stats;
    assert(course_schedule_with_allocator(vertices, edge, 1, tracked_allocate,
               tracked_release, &stats) == COURSE_SCHEDULE_POSSIBLE);
    assert(stats.used_csr && stats.initial_ready == 3001 && stats.max_ready == 3001);
    assert(stats.processed == vertices && stats.enqueued == vertices);
    assert(attempts == 4 && releases == 4 && live_blocks == 0 && live_bytes == 0);
    assert(peak_bytes == (3 * vertices + 1) * sizeof(size_t) + sizeof(int));
    printf("[OBSERVED] Course Schedule nonempty wide graph: %zu initially ready, "
           "%zu processed, %zu requested peak bytes.\n",
           stats.initial_ready, stats.processed, peak_bytes);
}

int main(void) {
    printf("[TEST] Course Schedule CSR checked practice...\n");
    const size_t fixed = test_fixed_graphs();
    size_t failures;
    const size_t exhaustive = test_exhaustive_graphs(&failures);
    const size_t invalid = test_invalid_arguments();
    const size_t arithmetic = test_checked_arithmetic();
    test_allocator_controls();
    test_wide_ready_queue();
    assert(exhaustive == 512 && failures == 2044 && fixed == 12 && arithmetic == 12);
    assert(live_blocks == 0 && live_bytes == 0);
    printf("[PASSED] Course Schedule CSR: %zu fixed fixtures, %zu exhaustive graphs, "
           "%zu allocation failures, %zu invalid cases, %zu arithmetic checks, "
           "2 allocated cleanup controls, 1 edgeless allocation control, "
           "1 nonempty wide-queue fixture; zero tracked blocks retained.\n\n",
           fixed, exhaustive, failures, invalid, arithmetic);
    return 0;
}
