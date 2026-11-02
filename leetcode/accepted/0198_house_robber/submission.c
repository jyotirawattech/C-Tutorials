#define MAX(a, b) ((a) > (b) ? (a) : (b))

int rob(int* nums, int numsSize) {
    // Edge cases
    if (numsSize == 0) return 0;
    if (numsSize == 1) return nums[0];

    // Hardware registers to track our moving DP state
    int prev2 = 0; // Represents dp[i-2]
    int prev1 = 0; // Represents dp[i-1]

    // The O(N) Sliding State Machine
    for (int i = 0; i < numsSize; i++) {
        // Calculate the optimal choice at the current step
        int current_max = MAX(prev1, prev2 + nums[i]);
        
        // Shift the DP window forward
        prev2 = prev1;
        prev1 = current_max;
    }

    // After processing the entire array, prev1 holds the absolute maximum profit
    return prev1;
}