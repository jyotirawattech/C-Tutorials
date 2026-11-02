#include <math.h>
#include <stdbool.h>

bool judgeSquareSum(int c) {
    // 1. HARDWARE FIX: Prevent 32-bit overflow by promoting to 64-bit registers
    long long left = 0;
    
    // 2. Mathematically bound the search space to O(sqrt(c))
    long long right = (long long)sqrt(c);
    
    // 3. The Converging State Machine
    while (left <= right) {
        long long current_sum = (left * left) + (right * right);
        
        if (current_sum == c) {
            return true; // We found the exact mathematical pair
        } else if (current_sum < c) {
            // The sum is too small, increase the floor
            left++;
        } else {
            // The sum is too large, decrease the ceiling
            right--;
        }
    }
    
    // Pointers crossed without finding a valid pair
    return false;
}