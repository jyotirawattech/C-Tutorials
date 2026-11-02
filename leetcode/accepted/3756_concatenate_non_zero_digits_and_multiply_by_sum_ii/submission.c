#define MOD 1000000007

int* sumAndMultiply(char * s, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int m = strlen(s);
    *returnSize = queriesSize;
    
    // Allocate the result array
    int* ans = (int*)malloc(queriesSize * sizeof(int));
    
    // 1. HARDWARE ALLOCATION: State Arrays
    // We allocate tracking arrays of size (m + 1) to make 1-based index math easier.
    // At ~2.8MB total, allocating this on the Call Stack would cause a Kernel Panic,
    // so we explicitly request Heap memory.
    int* C = (int*)malloc((m + 1) * sizeof(int));             // Count of non-zero digits
    long long* P = (long long*)malloc((m + 1) * sizeof(long long)); // Rolling Value modulo 10^9+7
    long long* S = (long long*)malloc((m + 1) * sizeof(long long)); // Prefix sum of all digits
    long long* p10 = (long long*)malloc((m + 1) * sizeof(long long)); // Powers of 10 modulo 10^9+7
    
    if (!ans || !C || !P || !S || !p10) return NULL; // Safety Check
    
    // Base states
    C[0] = 0;
    P[0] = 0;
    S[0] = 0;
    p10[0] = 1;
    
    // 2. The O(M) Preprocessing Sweep
    for (int i = 0; i < m; i++) {
        // Precompute powers of 10
        p10[i+1] = (p10[i] * 10) % MOD;
        
        // Track the continuous sum
        S[i+1] = S[i] + (s[i] - '0');
        
        if (s[i] != '0') {
            C[i+1] = C[i] + 1;
            P[i+1] = (P[i] * 10 + (s[i] - '0')) % MOD;
        } else {
            C[i+1] = C[i];
            P[i+1] = P[i];
        }
    }
    
    // 3. The O(1) Query Resolution Engine
    for (int i = 0; i < queriesSize; i++) {
        int l = queries[i][0];
        int r = queries[i][1];
        
        // O(1) Sum retrieval
        long long sum = S[r+1] - S[l];
        
        // O(1) Rolling Modulo Slicing
        int new_digits_count = C[r+1] - C[l];
        long long shifted_prefix = (P[l] * p10[new_digits_count]) % MOD;
        
        // C Modulo Safety: (A - B) % MOD can be negative in C. We add MOD to prevent this.
        long long x = (P[r+1] - shifted_prefix + MOD) % MOD;
        
        // Calculate the final answer
        ans[i] = (x * sum) % MOD;
    }
    
    // Clean up our Heavy State Arrays
    free(C); free(P); free(S); free(p10);
    
    return ans;
}