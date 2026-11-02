long long sumAndMultiply(int n) {
    // 1. HARDWARE FIX: 64-bit registers
    // The product of x and sum can exceed 80 billion, which will 
    // instantly overflow a standard 32-bit signed integer.
    long long x = 0;
    long long sum = 0;
    long long multiplier = 1; // Tracks the base-10 place value (1, 10, 100...)

    // 2. The O(log N) Mathematical Peel
    // We peel digits from right to left.
    while (n > 0) {
        int digit = n % 10;
        n /= 10; // Shift the original number down

        // 3. The Zero-Filter State Machine
        if (digit != 0) {
            // "Prepend" the digit mathematically to x
            x += digit * multiplier;
            
            // Advance our place-value multiplier for the NEXT non-zero digit
            multiplier *= 10;
            
            // Accumulate the digit sum
            sum += digit;
        }
    }

    // Return the final product safely within 64-bit bounds
    return x * sum;
}