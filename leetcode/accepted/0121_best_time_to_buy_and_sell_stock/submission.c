int maxProfit(int* prices, int pricesSize) {
    // Hardware safety check
    if (pricesSize <= 1) {
        return 0;
    }

    // 1. Initialize our State Registers
    // We set the initial "lowest price" to the first day's price.
    int min_price = prices[0];
    int max_profit = 0;

    // 2. The O(N) Forward Time Sweep
    for (int i = 1; i < pricesSize; i++) {
        
        // Branch A: We found a new historical low!
        // We cannot sell today for a profit (since the price dropped),
        // but we update our min_price register for future days.
        if (prices[i] < min_price) {
            min_price = prices[i];
        } 
        // Branch B: The price went up. 
        // Calculate the profit if we sold today, and update max_profit if it's a new record.
        else if (prices[i] - min_price > max_profit) {
            max_profit = prices[i] - min_price;
        }
    }

    return max_profit;
}