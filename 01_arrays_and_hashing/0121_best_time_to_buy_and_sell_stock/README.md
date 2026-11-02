# 0121 — Best Time to Buy and Sell Stock

Public problem: [LeetCode 121](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)

## Source and dates

- **Accepted source:** [submission 2046785680](https://leetcode.com/submissions/detail/2046785680/), verified as Jyoti Rawat's C submission on profile `user0592I`.
- **Platform result observed:** Accepted, 212/212 test cases passed.
- **Displayed submission time:** 26 June 2026, 17:29. The page did not specify a timezone; this is not converted to IST or UTC.
- **Original practice date and assistance:** Unknown. The submission timestamp is evidence of that accepted submission, not an earlier practice history or proof of unaided authorship.
- **Archive preparation:** 2 November 2026. The accepted function's algorithm is preserved; repository formatting, this explanation and the additional local tests were prepared with AI assistance.
- **GitHub archive date:** 2 November 2026. This entry is not a newly solved problem on the archive date; the accepted submission is dated separately above.

## Task and constraints

Choose a purchase day and a later sale day to maximize one transaction's profit.
Return zero if every permitted transaction loses money. The input is a readable
array of 1–100000 prices, each in the range 0–10000. The function does not modify it.
The original function additionally returns zero for an empty input.

For `[7, 1, 5, 3, 6, 4]`, buying at 1 and selling later at 6 yields 5.
The later low price must never be paired with an earlier sale.

## Approach and invariant

Scan from left to right, retaining the smallest price already encountered and the
best valid profit found so far. For each next price:

1. If it is a new minimum, record it as a possible purchase price for later days.
2. Otherwise, compare selling now against that minimum with the best profit.

After processing each day, `min_price` is the smallest price in the processed
prefix, and `max_profit` is the best nonnegative buy-before-sell profit inside
that prefix. A new minimum cannot improve today's profit, which is why the two
updates can be an `if`/`else if`. The initial best profit of zero covers declining
and constant-price inputs.

Enumerating every buy/sell pair is a simpler O(n²) alternative. It is used only
as an independent oracle for small local test arrays. The submitted scan avoids
that repeated work without storing another array.

## Complexity and memory

- **Time:** O(n), one pass over n prices.
- **Auxiliary space:** O(1), two retained values and a loop index.
- **Ownership:** the caller owns the array; the function allocates and frees nothing.
- **Arithmetic:** the stated 0–10000 price range bounds differences; arbitrary out-of-contract integer ranges are not supported or claimed safe by this archive.

## Local validation

From the repository root:

```sh
make test
```

The standalone harness in `solution.c` includes:

| Test group | Expected behavior |
| --- | --- |
| Normal example, rising and falling prices | Best later sale; zero when no gain exists |
| Equal values, one day and two days | No fabricated transaction or same-day profit |
| Minimum appearing last; new lower minimum | Preserve the best valid earlier trade; use a later minimum only for later sales |
| Prices at 0 and 10000 | Bounded maximum profit of 10000 |
| Empty-input guard | Zero without dereferencing the pointer |
| 1024 deterministic short arrays | Match an independent exhaustive buy/sell oracle |
| 100000 prices | Correct result at the stated maximum input length |

**Observed local run, 2 November 2026:** `make test` passed all 12 solution
harnesses and six runner regressions with fail-fast UBSan on Apple Clang 17,
arm64 macOS 27.2. This entry passed all eleven fixed cases, 1024 oracle comparisons
and the maximum-length case. Twelve separate `leaks` invocations returned zero,
but reported restricted-process notices; this is a bounded detector observation,
not a universal memory-safety guarantee. ASan was not run for this addition.

Repository tests are separate from the historical platform receipt; neither
claims production use.
