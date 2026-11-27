# Time Needed to Buy Tickets

Each buyer gets one ticket per turn. A buyer who still needs tickets rejoins
the end of the queue. For `[2, 3, 2]`, buyer 1 finishes after seven ticket
sales. The calculation stops at the target buyer's final ticket.

This is AI-assisted C11 practice for [LeetCode 2073](https://leetcode.com/problems/time-needed-to-buy-tickets/),
dated 27 November 2026. The [archive](../../leetcode/accepted/2073_time_needed_to_buy_tickets/)
preserves the [original Accepted C submission](https://leetcode.com/submissions/detail/2033036947/)
and its displayed submission date. Original practice date and assistance are
unknown. Judge verdict, runtime, memory and Beats for this adaptation are
**Not captured**.

## Count each buyer's contribution

Let `t` be the target's requested ticket count. Buyers at or before the target
have up to `t` turns by the stopping point. Buyers after the target have up to
`t - 1` turns because the final round ends at the target. Each buyer can also
leave early, so cap their contribution at the number of tickets they need.
The running sum counts sales by processed buyers up to the same stopping point.

`ticketTime(tickets, count, target, &elapsed)` accepts a readable array of
positive `uint64_t` counts, a valid zero-based target and separate writable
output storage. The input is unchanged. On success it stores the total in
`elapsed`. Invalid data and arithmetic overflow return distinct statuses,
and both leave the output untouched. It checks the target and byte extent
before reading the target count. The caller supplies valid storage for the
declared extent. After the target checks, the scan returns the first invalid
count or overflowing addition it encounters.

## How much better, and why?

The archived C source already uses a **capped per-buyer sweep**. On their
shared domain, both scans visit `n` buyers in Θ(n) time and use O(1) auxiliary
space. This version adds range checks and guards every addition. It can return
totals through `UINT64_MAX` and reports larger sums explicitly. The archive
uses `int` and assumes the sum fits its judge contract. The improvement is a
wider, checked result contract. No growth-rate or timing advantage over the
archived sweep is established.

For comparison, a literal FIFO simulator with an explicit queue and working
ticket counts takes Θ(n + T) time and O(n) auxiliary space, where `T` is the
number of tickets actually sold before stopping. It processes every sale.
For four buyers needing 1,000,000 tickets each and target index 1, the formula
returns 3,999,998. A FIFO loop would process that many sale events. The sweep
makes four buyer contributions. The large case checks the formula using
synthetic input. A sale event and a buyer contribution are different work
units. The sweep avoids simulating the queue when only the final total matters.

Paired benchmark **Not run**. Measured elapsed-time and process-memory gains
are unknown.

## Tests

Run `make test` from the repository root. The standalone harness checks every
target over small queues with one to five buyers and ticket counts from one
to four against a literal FIFO simulation. It also exercises a large modeled
total, the exact `UINT64_MAX` boundary, overflow, invalid arguments and
unchanged output on error.
