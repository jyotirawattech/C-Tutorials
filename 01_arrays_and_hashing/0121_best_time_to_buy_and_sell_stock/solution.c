/**
 * LeetCode 0121: Best Time to Buy and Sell Stock
 * Source: https://leetcode.com/submissions/detail/2046785680/
 *
 * The maxProfit function preserves the verified accepted C submission's
 * algorithm. Formatting, this explanation and standalone tests were added
 * with AI assistance for the repository archive on 2 November 2026.
 * Original solution assistance is unknown; this is not a new solve-date claim.
 *
 * Contract: prices points to pricesSize readable integers when pricesSize > 0.
 * LeetCode's price range 0..10000 keeps the price difference within int.
 * No allocation, ownership transfer or input mutation occurs.
 * Time O(n); auxiliary space O(1), excluding this standalone test harness.
 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

int maxProfit(int* prices, int pricesSize) {
    if (pricesSize <= 1) return 0;

    int min_price = prices[0];
    int max_profit = 0;

    for (int i = 1; i < pricesSize; i++) {
        if (prices[i] < min_price) {
            min_price = prices[i];
        } else if (prices[i] - min_price > max_profit) {
            max_profit = prices[i] - min_price;
        }
    }

    return max_profit;
}

/* Independent O(n^2) test oracle: enumerate every buy-before-sell pair. */
static int brute_force_profit(const int* prices, int count) {
    int best = 0;
    for (int buy = 0; buy < count; buy++) {
        for (int sell = buy + 1; sell < count; sell++) {
            int profit = prices[sell] - prices[buy];
            if (profit > best) best = profit;
        }
    }
    return best;
}

static void test_fixed_cases(void) {
    int normal[] = {7, 1, 5, 3, 6, 4};
    int descending[] = {7, 6, 4, 3, 1};
    int increasing[] = {1, 2, 3, 4, 5};
    int repeated[] = {5, 5, 5, 5};
    int single[] = {5};
    int two_days[] = {2, 3};
    int low_late[] = {4, 7, 1};
    int new_minimum[] = {3, 8, 1, 9};
    int max_range[] = {10000, 0, 10000};
    int no_recovery[] = {10000, 0};

    assert(maxProfit(normal, 6) == 5);
    assert(maxProfit(descending, 5) == 0);
    assert(maxProfit(increasing, 5) == 4);
    assert(maxProfit(repeated, 4) == 0);
    assert(maxProfit(single, 1) == 0);
    assert(maxProfit(two_days, 2) == 1);
    assert(maxProfit(low_late, 3) == 3);
    assert(maxProfit(new_minimum, 4) == 8);
    assert(maxProfit(max_range, 3) == 10000);
    assert(maxProfit(no_recovery, 2) == 0);
    /* The archived function also returns before reading an empty input. */
    assert(maxProfit(NULL, 0) == 0);
}

static void test_against_oracle(void) {
    uint32_t state = UINT32_C(121);
    int prices[8];

    /* A fixed seed generates reproducible test data, not security randomness. */
    for (int count = 1; count <= 8; count++) {
        for (int sample = 0; sample < 128; sample++) {
            for (int i = 0; i < count; i++) {
                state = state * UINT32_C(1664525) + UINT32_C(1013904223);
                prices[i] = (int)(state % UINT32_C(10001));
            }
            assert(maxProfit(prices, count) == brute_force_profit(prices, count));
        }
    }
}

static void test_maximum_length(void) {
    /* Static storage keeps the large test fixture off the call stack. */
    static int prices[100000];
    for (int i = 0; i < 100000; i++) prices[i] = i % 10001;
    assert(maxProfit(prices, 100000) == 10000);
}

int main(void) {
    test_fixed_cases();
    test_against_oracle();
    test_maximum_length();
    printf("[PASS] 0121: 11 fixed cases, 1024 oracle comparisons, maximum-length case\n");
    return 0;
}
