/*
 * Checked bracket-span practice, C11. AI-assisted adaptation, 2026-11-17.
 * Exact platform acceptance for this API/implementation: Not captured.
 */
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BRACKETS_NO_TEST_MAIN
static void *test_allocate(size_t bytes);
static void test_release(void *pointer);
#define BRACKETS_MALLOC test_allocate
#define BRACKETS_FREE test_release
#else
#if defined(BRACKETS_MALLOC) != defined(BRACKETS_FREE)
#error "Supply both BRACKETS_MALLOC and BRACKETS_FREE, or neither"
#endif
#ifndef BRACKETS_MALLOC
#define BRACKETS_MALLOC malloc
#define BRACKETS_FREE free
#endif
#endif

typedef enum {
    BRACKETS_VALID,
    BRACKETS_INVALID,
    BRACKETS_INVALID_ARGUMENT,
    BRACKETS_ALLOCATION_FAILURE
} BracketStatus;

/*
 * data borrows length readable bytes, with NULL permitted only at length 0.
 * No terminator is required; embedded NUL and every non-bracket byte are invalid.
 * Input remains unchanged. Hooks, if supplied, must be a matching malloc/free pair.
 */
BracketStatus validateBracketsChecked(const char *data, size_t length) {
    if (!data && length != 0) return BRACKETS_INVALID_ARGUMENT;
    if (length == 0) return BRACKETS_VALID;
    if (length % 2 != 0) return BRACKETS_INVALID;

    /*
     * A valid even-length span has exactly length/2 opening brackets.
     * More pending openings already makes validity impossible, so rejecting
     * before a push beyond this capacity cannot reject a valid sequence.
     */
    size_t capacity = length / 2;
    char *expected = BRACKETS_MALLOC(capacity);
    if (!expected) return BRACKETS_ALLOCATION_FAILURE;
    size_t depth = 0;
    BracketStatus result = BRACKETS_INVALID;
    for (size_t i = 0; i < length; ++i) {
        char closing;
        switch (data[i]) {
            case '(': closing = ')'; break;
            case '[': closing = ']'; break;
            case '{': closing = '}'; break;
            case ')':
            case ']':
            case '}':
                if (depth == 0 || expected[depth - 1] != data[i])
                    goto done;
                --depth;
                continue;
            default:
                goto done;
        }
        if (depth == capacity) goto done;
        expected[depth] = closing;
        ++depth;
    }
    if (depth == 0) result = BRACKETS_VALID;
done:
    BRACKETS_FREE(expected);
    return result;
}

#ifndef BRACKETS_NO_TEST_MAIN
/* Standalone tests own one tracked validator allocation at a time. */
static void *test_live_pointer;
static size_t test_attempts, test_releases, test_requested_bytes;
static bool test_fail_allocation;
static size_t test_oracle_cases, test_failure_cases;

static void *test_allocate(size_t bytes) {
    ++test_attempts;
    test_requested_bytes = bytes;
    assert(bytes > 0);
    assert(!test_live_pointer);
    if (test_fail_allocation) return NULL;
    void *pointer = malloc(bytes);
    if (pointer) test_live_pointer = pointer;
    return pointer;
}
static void test_release(void *pointer) {
    assert(pointer && pointer == test_live_pointer);
    test_live_pointer = NULL;
    ++test_releases;
    free(pointer);
}
static void reset_allocator(void) {
    assert(!test_live_pointer);
    test_attempts = test_releases = test_requested_bytes = 0;
    test_fail_allocation = false;
}
static void expect_status(const char *data, size_t length,
                          BracketStatus expected) {
    reset_allocator();
    assert(validateBracketsChecked(data, length) == expected);
    assert(!test_live_pointer);
    if (data && length != 0 && length % 2 == 0) {
        assert(test_attempts == 1 && test_releases == 1);
        assert(test_requested_bytes == length / 2);
    } else {
        assert(test_attempts == 0 && test_releases == 0);
    }
}
#define CHECK_LITERAL(text, status) \
    expect_status((text), sizeof(text) - 1, (status))

/* Independent short-input grammar: S := empty | '(' S ')' S | ... . */
static bool grammar_valid(const char *data, size_t length) {
    if (length == 0) return true;
    if (length % 2 != 0) return false;
    char closing;
    switch (data[0]) {
        case '(': closing = ')'; break;
        case '[': closing = ']'; break;
        case '{': closing = '}'; break;
        default: return false;
    }
    for (size_t split = 1; split < length; split += 2) {
        if (data[split] == closing &&
            grammar_valid(data + 1, split - 1) &&
            grammar_valid(data + split + 1, length - split - 1))
            return true;
    }
    return false;
}
static void compare_to_grammar(const char *data, size_t length) {
    assert(length <= 32);
    char original[32];
    for (size_t i = 0; i < length; ++i) original[i] = data[i];
    bool valid = grammar_valid(data, length);
    expect_status(data, length, valid ? BRACKETS_VALID : BRACKETS_INVALID);
    for (size_t i = 0; i < length; ++i) assert(data[i] == original[i]);
    ++test_oracle_cases;
}
static void enumerate(char *data, size_t position, size_t length) {
    static const char alphabet[] = {'(', ')', '[', ']', '{', '}', 'x', '\0'};
    if (position == length) {
        compare_to_grammar(data, length);
        return;
    }
    for (size_t i = 0; i < sizeof alphabet; ++i) {
        data[position] = alphabet[i];
        enumerate(data, position + 1, length);
    }
}
static uint32_t next_random(uint32_t *state) {
    *state = *state * UINT32_C(1664525) + UINT32_C(1013904223);
    return *state;
}
static void fixed_syntax_group(void) {
    CHECK_LITERAL("()", BRACKETS_VALID);
    CHECK_LITERAL("()[]{}", BRACKETS_VALID);
    CHECK_LITERAL("([{}])", BRACKETS_VALID);
    CHECK_LITERAL("{[()]}[{}]()", BRACKETS_VALID);
    CHECK_LITERAL("(]", BRACKETS_INVALID);
    CHECK_LITERAL("([)]", BRACKETS_INVALID);
    CHECK_LITERAL("][", BRACKETS_INVALID);
    CHECK_LITERAL("((()", BRACKETS_INVALID);
    CHECK_LITERAL(")))(", BRACKETS_INVALID);
    CHECK_LITERAL("((((", BRACKETS_INVALID);
    CHECK_LITERAL("[", BRACKETS_INVALID);
}
static void span_group(void) {
    expect_status(NULL, 0, BRACKETS_VALID);
    expect_status(NULL, 1, BRACKETS_INVALID_ARGUMENT);
    expect_status(NULL, 2, BRACKETS_INVALID_ARGUMENT);
    CHECK_LITERAL("", BRACKETS_VALID);
    /* No terminator; the third byte is outside this two-byte view. */
    const char raw[] = {'(', ')', 'x'};
    expect_status(raw, 2, BRACKETS_VALID);
    expect_status(raw, 3, BRACKETS_INVALID);
    const char embedded_zero[] = {'(', ')', '\0', '\0'};
    expect_status(embedded_zero, sizeof embedded_zero, BRACKETS_INVALID);
    CHECK_LITERAL("ab", BRACKETS_INVALID);
    reset_allocator();
    test_fail_allocation = true;
    assert(validateBracketsChecked(NULL, 0) == BRACKETS_VALID);
    assert(validateBracketsChecked("x", 1) == BRACKETS_INVALID);
    assert(test_attempts == 0);
}
static void failure_group(void) {
    static const struct { const char *data; size_t length; } cases[] = {
        {"()", 2}, {"([{}])", 6}, {"([)]", 4}, {"xxxx", 4}
    };
    for (size_t c = 0; c < sizeof cases / sizeof cases[0]; ++c) {
        reset_allocator();
        test_fail_allocation = true;
        assert(validateBracketsChecked(cases[c].data, cases[c].length) ==
               BRACKETS_ALLOCATION_FAILURE);
        assert(test_attempts == 1 && test_releases == 0 && !test_live_pointer);
        ++test_failure_cases;
    }
}
static void exhaustive_group(void) {
    char data[6];
    for (size_t length = 0; length <= sizeof data; ++length)
        enumerate(data, 0, length);
}
static void seeded_group(void) {
    static const char alphabet[] = {'(', ')', '[', ']', '{', '}', 'x', '\0'};
    uint32_t state = UINT32_C(0x17202026);
    char data[32];
    for (size_t c = 0; c < 20000; ++c) {
        size_t length = (size_t)((next_random(&state) >> 16) % 33u);
        for (size_t i = 0; i < length; ++i)
            data[i] = alphabet[(next_random(&state) >> 16) % (sizeof alphabet)];
        compare_to_grammar(data, length);
    }
}
static void deep_group(void) {
    const size_t pairs = 100000;
    char *data = malloc(pairs * 2);
    assert(data);
    for (size_t i = 0; i < pairs; ++i) data[i] = '(';
    for (size_t i = pairs; i < pairs * 2; ++i) data[i] = ')';
    expect_status(data, pairs * 2, BRACKETS_VALID);
    for (size_t i = 0; i < pairs; ++i) assert(data[i] == '(');
    for (size_t i = pairs; i < pairs * 2; ++i) assert(data[i] == ')');
    data[pairs] = '('; /* The next push exceeds the proven maximum. */
    expect_status(data, pairs * 2, BRACKETS_INVALID);
    data[pairs] = ')';
    data[pairs * 2 - 1] = ']';
    expect_status(data, pairs * 2, BRACKETS_INVALID);
    free(data);
}
static void resource_and_byte_group(void) {
    CHECK_LITERAL("([{}])", BRACKETS_VALID);
    assert(test_attempts == 1 && test_requested_bytes == 3 &&
           test_releases == 1);
    for (unsigned int value = 0; value < 256u; ++value) {
        unsigned char data[] = {(unsigned char)value, (unsigned char)')'};
        unsigned char first = data[0], second = data[1];
        expect_status((const char *)data, 2,
                      value == (unsigned int)'(' ? BRACKETS_VALID
                                                : BRACKETS_INVALID);
        assert(data[0] == first && data[1] == second);
    }
}
int main(void) {
    printf("[TEST] Checked LeetCode 0020 bracket-span practice...\n");
    fixed_syntax_group();
    span_group();
    failure_group();
    exhaustive_group();
    seeded_group();
    deep_group();
    resource_and_byte_group();
    assert(!test_live_pointer);
    printf("[PASSED] Valid Parentheses: 7 groups, %zu oracle cases, "
           "%zu allocation failure cases, zero tracked blocks retained.\n\n",
           test_oracle_cases, test_failure_cases);
    return 0;
}
#endif
