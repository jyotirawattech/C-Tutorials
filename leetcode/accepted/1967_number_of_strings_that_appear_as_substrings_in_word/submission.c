int numOfStrings(char ** patterns, int patternsSize, char * word) {
    int count = 0;
    
    // 1. The Zero-Allocation Sweep
    for (int i = 0; i < patternsSize; i++) {
        
        // 2. Hardware-Optimized Intrinsic
        // strstr returns a pointer to the first occurrence of patterns[i] inside word.
        // If it returns NULL, the pattern is not a substring.
        // For strings bounded at 100 chars, this executes in L1 cache almost instantly.
        if (strstr(word, patterns[i]) != NULL) {
            count++;
        }
    }
    
    return count;
}