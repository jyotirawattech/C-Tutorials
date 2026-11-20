/**
 * Problem: LeetCode 0021 - Merge Two Sorted Lists
 * Language: C (C11)
 *
 * Approach:
 * Uses a stack-allocated sentinel dummy node to eliminate edge-case branching
 * for the new list head. Merges existing node pointers directly without allocating
 * any new nodes (zero heap allocation during merge).
 *
 * Complexity:
 * - Time: O(M + N) where M and N are lengths of the lists.
 * - Space: O(1) in-place pointer splicing.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>

#ifdef NDEBUG
#error "The standalone harness requires assertions."
#endif

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    struct ListNode dummy;
    dummy.next = NULL;
    struct ListNode* tail = &dummy;

    while (list1 != NULL && list2 != NULL) {
        if (list1->val <= list2->val) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    tail->next = (list1 != NULL) ? list1 : list2;
    return dummy.next;
}

/* ========================================================================= */
/* Bounded ownership oracle and standalone test fixtures                      */
/* ========================================================================= */

struct NodeRecord {
    struct ListNode* node;
    int value;
    size_t origin;
    size_t ordinal;
};

static void* fixture_array(size_t count, size_t element_size) {
    if (count == 0) return NULL;
    assert(element_size != 0 && count <= SIZE_MAX / element_size);
    void* memory = malloc(count * element_size);
    assert(memory != NULL);
    return memory;
}

/* Sort immutable value/origin snapshots, independently of merge's branches. */
static int compare_records(const void* a, const void* b) {
    const struct NodeRecord* left = a;
    const struct NodeRecord* right = b;
    if (left->value != right->value)
        return (left->value > right->value) - (left->value < right->value);
    if (left->origin != right->origin)
        return (left->origin > right->origin) - (left->origin < right->origin);
    return (left->ordinal > right->ordinal) - (left->ordinal < right->ordinal);
}

/* Never follow or dereference an unexpected pointer; inspect at most count nodes. */
static bool oracle_matches(const struct ListNode* head,
                           const struct NodeRecord* expected, size_t count) {
    const struct ListNode* current = head;
    for (size_t i = 0; i < count; ++i) {
        if (current != expected[i].node) return false;
        if (current->val != expected[i].value) return false;
        current = current->next;
    }
    return current == NULL;
}

static void run_case(const int* left, size_t m, const int* right, size_t n) {
    assert((m == 0 || left != NULL) && (n == 0 || right != NULL));
    assert(m <= SIZE_MAX - n);
    const size_t total = m + n;
    struct ListNode* nodes = fixture_array(total, sizeof(*nodes));
    struct NodeRecord* expected = fixture_array(total, sizeof(*expected));
    for (size_t origin = 0; origin < 2; ++origin) {
        const int* values = origin == 0 ? left : right;
        const size_t count = origin == 0 ? m : n;
        const size_t offset = origin == 0 ? 0 : m;
        for (size_t i = 0; i < count; ++i) {
            assert(i == 0 || values[i - 1] <= values[i]);
            const size_t at = offset + i;
            nodes[at].val = values[i];
            nodes[at].next = i + 1 < count ? &nodes[at + 1] : NULL;
            expected[at] = (struct NodeRecord){&nodes[at], values[i], origin, i};
        }
    }
    if (total > 1) qsort(expected, total, sizeof(*expected), compare_records);
    struct ListNode* result = mergeTwoLists(m == 0 ? NULL : nodes,
                                           n == 0 ? NULL : &nodes[m]);
    assert(oracle_matches(result, expected, total));
    /* Fixture ownership is independent of the links rewritten by merge. */
    free(expected);
    free(nodes);
}

static size_t test_fixed_cases(void) {
    const int a[] = {1, 2, 4}, b[] = {1, 3, 4}, zero[] = {0};
    const int duplicates_a[] = {1, 1, 3}, duplicates_b[] = {1, 2, 3};
    const int lower[] = {-3, -2, -1}, upper[] = {0, 1, 2};
    const int bounds_a[] = {INT_MIN, 0, INT_MAX};
    const int bounds_b[] = {INT_MIN, INT_MAX};
    const int dense[] = {-2, -1, 0, 0, 1, 2};
    const int even[] = {0, 2, 4, 6}, odd[] = {1, 3, 5};
    run_case(a, 3, b, 3);                  /* Original normal fixture. */
    run_case(NULL, 0, NULL, 0);            /* Both empty. */
    run_case(NULL, 0, zero, 1);            /* Original left-empty fixture. */
    run_case(zero, 1, NULL, 0);            /* Right empty. */
    run_case(duplicates_a, 3, duplicates_b, 3);
    run_case(lower, 3, upper, 3);          /* Append the right tail. */
    run_case(upper, 3, lower, 3);          /* Append the left tail. */
    run_case(bounds_a, 3, bounds_b, 2);    /* No subtraction-overflow oracle. */
    run_case(zero, 1, dense, 6);           /* Imbalanced duplicate values. */
    run_case(even, 4, odd, 3);             /* Alternating selections. */
    return 10;
}

enum { MAX_SHORT_LENGTH = 5, SEQUENCE_COUNT = 56 };
struct Sequence {
    size_t length;
    int values[MAX_SHORT_LENGTH];
};

static void collect_sequences(struct Sequence* sequences, size_t* count,
                              int* values, size_t length, int minimum) {
    assert(*count < SEQUENCE_COUNT);
    sequences[*count].length = length;
    for (size_t i = 0; i < length; ++i) sequences[*count].values[i] = values[i];
    ++*count;
    if (length == MAX_SHORT_LENGTH) return;
    for (int value = minimum; value <= 1; ++value) {
        values[length] = value;
        collect_sequences(sequences, count, values, length + 1, value);
    }
}

static size_t test_exhaustive_pairs(void) {
    struct Sequence sequences[SEQUENCE_COUNT];
    int values[MAX_SHORT_LENGTH];
    size_t count = 0, pairs = 0;
    collect_sequences(sequences, &count, values, 0, -1);
    assert(count == SEQUENCE_COUNT);
    for (size_t a = 0; a < count; ++a) {
        for (size_t b = 0; b < count; ++b) {
            run_case(sequences[a].values, sequences[a].length,
                     sequences[b].values, sequences[b].length);
            ++pairs;
        }
    }
    assert(pairs == 3136);
    return pairs;
}

static void test_long_case(void) {
    enum { EACH_LENGTH = 20000 };
    int* left = fixture_array(EACH_LENGTH, sizeof(*left));
    int* right = fixture_array(EACH_LENGTH, sizeof(*right));
    for (size_t i = 0; i < EACH_LENGTH; ++i) {
        left[i] = (int)(2 * i);
        right[i] = (int)(2 * i + 1);
    }
    run_case(left, EACH_LENGTH, right, EACH_LENGTH);
    free(right);
    free(left);
}

/* These malformed graphs test only the oracle, never merge's input contract. */
static size_t test_oracle_rejections(void) {
    struct ListNode a = {1, NULL}, b = {1, NULL}, foreign = {1, NULL};
    struct ListNode copy = {1, &b};
    const struct NodeRecord expected[] = {{&a, 1, 0, 0}, {&b, 1, 1, 0}};
    a.next = &b;
    assert(oracle_matches(&a, expected, 2));
    assert(!oracle_matches(NULL, expected, 2));       /* Missing head. */
    a.next = NULL;
    assert(!oracle_matches(&a, expected, 2));         /* Dropped tail. */
    a.next = &b;
    assert(!oracle_matches(&copy, expected, 2));      /* Same values, new node. */
    foreign.next = &b;
    assert(!oracle_matches(&foreign, expected, 2));   /* Foreign original set. */
    a.next = &a;
    assert(!oracle_matches(&a, expected, 2));         /* Duplicate/cycle. */
    a.next = &b;
    b.next = &foreign;
    assert(!oracle_matches(&a, expected, 2));         /* Extra trailing node. */
    b.next = NULL;
    a.val = 2;
    assert(!oracle_matches(&a, expected, 2));         /* Snapshot value changed. */
    a.val = 1;
    a.next = NULL;
    b.next = &a;
    assert(!oracle_matches(&b, expected, 2));         /* Right-before-left tie. */
    assert(!oracle_matches(&a, NULL, 0));             /* Nonempty empty result. */
    return 9;
}

int main(void) {
    printf("[TEST] Running LeetCode 0021: Merge Two Sorted Lists ownership tests...\n");
    const size_t fixed = test_fixed_cases();
    const size_t exhaustive = test_exhaustive_pairs();
    test_long_case();
    const size_t rejected = test_oracle_rejections();
    printf("[PASSED] Merge Two Sorted Lists: %zu fixed cases, %zu exhaustive pairs, "
           "1 long case (40000 nodes), %zu oracle rejection cases.\n\n",
           fixed, exhaustive, rejected);
    return 0;
}
