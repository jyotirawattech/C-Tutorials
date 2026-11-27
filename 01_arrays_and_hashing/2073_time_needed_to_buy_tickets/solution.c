#include <stddef.h>
#include <stdint.h>

typedef enum {
    TICKET_TIME_OK,
    TICKET_TIME_INVALID,
    TICKET_TIME_OVERFLOW
} TicketStatus;

/*
 * tickets must name count readable positive counts.
 * elapsed is disjoint writable storage and is updated only on success.
 */
TicketStatus ticketTime(const uint64_t *tickets, size_t count, size_t target,
                        uint64_t *elapsed) {
    if (tickets == NULL || elapsed == NULL || target >= count ||
        count > SIZE_MAX / sizeof *tickets || tickets[target] == 0) {
        return TICKET_TIME_INVALID;
    }

    uint64_t last_round = tickets[target];
    uint64_t total = 0;
    for (size_t i = 0; i < count; ++i) {
        if (tickets[i] == 0) {
            return TICKET_TIME_INVALID;
        }
        uint64_t limit = i <= target ? last_round : last_round - 1;
        uint64_t served = tickets[i] < limit ? tickets[i] : limit;
        if (served > UINT64_MAX - total) {
            return TICKET_TIME_OVERFLOW;
        }
        total += served;
    }

    *elapsed = total;
    return TICKET_TIME_OK;
}

#ifndef TICKET_TIME_NO_TEST_MAIN
#include <assert.h>
#include <stdio.h>

/* Literal turns through a circular queue, retaining a buyer until done. */
static uint64_t simulate(const uint64_t *tickets, size_t count, size_t target) {
    uint64_t remaining[5];
    size_t queue[5];
    assert(count > 0 && count <= 5);
    for (size_t i = 0; i < count; ++i) {
        remaining[i] = tickets[i];
        queue[i] = i;
    }

    size_t head = 0;
    size_t tail = 0; /* The circular queue starts full. */
    uint64_t time = 0;
    for (;;) {
        size_t buyer = queue[head];
        head = (head + 1) % count;
        --remaining[buyer];
        ++time;
        if (remaining[buyer] == 0) {
            if (buyer == target) {
                return time;
            }
        } else {
            queue[tail] = buyer;
            tail = (tail + 1) % count;
        }
    }
}

static size_t checkSmallQueues(void) {
    size_t cases = 0;
    size_t layouts = 1;
    for (size_t n = 1; n <= 5; ++n) {
        layouts *= 4;
        for (size_t code = 0; code < layouts; ++code) {
            uint64_t tickets[5];
            size_t digits = code;
            for (size_t i = 0; i < n; ++i) {
                tickets[i] = digits % 4 + 1;
                digits /= 4;
            }
            for (size_t target = 0; target < n; ++target) {
                uint64_t elapsed = 0;
                assert(ticketTime(tickets, n, target, &elapsed) == TICKET_TIME_OK);
                assert(elapsed == simulate(tickets, n, target));
                ++cases;
            }
        }
    }
    return cases;
}

static void checkBoundaries(void) {
    const uint64_t model[] = {1000000, 1000000, 1000000, 1000000};
    uint64_t elapsed = 0;
    assert(ticketTime(model, 4, 1, &elapsed) == TICKET_TIME_OK);
    assert(elapsed == 3999998);

    const uint64_t maximum[] = {UINT64_MAX - 1, 1};
    assert(ticketTime(maximum, 2, 0, &elapsed) == TICKET_TIME_OK);
    assert(elapsed == UINT64_MAX);

    const uint64_t overflow[] = {UINT64_MAX, 1};
    elapsed = 42;
    assert(ticketTime(overflow, 2, 0, &elapsed) == TICKET_TIME_OVERFLOW);
    const uint64_t zero[] = {1, 0};
    assert(ticketTime(zero, 2, 0, &elapsed) == TICKET_TIME_INVALID);
    assert(ticketTime(zero, 2, 1, &elapsed) == TICKET_TIME_INVALID);
    assert(ticketTime(zero, 2, 2, &elapsed) == TICKET_TIME_INVALID);
    assert(ticketTime(zero, 0, 0, &elapsed) == TICKET_TIME_INVALID);
    assert(ticketTime(NULL, 2, 0, &elapsed) == TICKET_TIME_INVALID);
    assert(ticketTime(model, 4, 0, NULL) == TICKET_TIME_INVALID);
    if (sizeof *model > 1) {
        assert(ticketTime(model, SIZE_MAX / sizeof *model + 1, 0, &elapsed)
               == TICKET_TIME_INVALID);
    }
    assert(elapsed == 42);
}

int main(void) {
    size_t cases = checkSmallQueues();
    checkBoundaries();
    printf("[PASSED] Ticket Time: %zu FIFO oracle cases, exact wide total, overflow and invalid inputs.\n", cases);
    return 0;
}
#endif
