int minimumCost(int* cost, int costSize) {
    // 1. HARDWARE EXPLOIT: Constraint cost[i] <= 100
    // We allocate a tiny 101-element frequency array on the Call Stack.
    // At exactly 404 bytes, this safely avoids Stack Overflow and 
    // guarantees a 100% L1 CPU Cache hit rate.
    int freq[101] = {0};
    
    // Map the frequencies in exactly O(N) time
    for (int i = 0; i < costSize; i++) {
        freq[cost[i]]++;
    }
    
    int total_cost = 0;
    int cart_size = 0; // Tracks the current buy/free cycle
    
    // 2. The Greedy Sweep
    // We iterate backward to grab the most expensive candies first.
    for (int val = 100; val >= 1; val--) {
        while (freq[val] > 0) {
            if (cart_size == 2) {
                // We have bought 2 candies in this cycle. 
                // We take this high-value candy for free!
                cart_size = 0; // Reset the cycle
            } else {
                // We must pay for this candy.
                total_cost += val;
                cart_size++;
            }
            // Decrement the availability of this specific price
            freq[val]--;
        }
    }
    
    return total_cost;
}