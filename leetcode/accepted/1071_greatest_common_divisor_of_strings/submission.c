

// Standard Euclidean Algorithm for Greatest Common Divisor
int get_gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

char * gcdOfStrings(char * str1, char * str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int total_len = len1 + len2;
    
    // 1. Virtual Concatenation Check (Zero memory allocation!)
    // We check if (str1 + str2) == (str2 + str1) mathematically
    for (int i = 0; i < total_len; i++) {
        // Evaluate what character would be at index i for str1 + str2
        char char_concat_A = (i < len1) ? str1[i] : str2[i - len1];
        
        // Evaluate what character would be at index i for str2 + str1
        char char_concat_B = (i < len2) ? str2[i] : str1[i - len2];
        
        // If the concatenated versions differ, no divisor is possible
        if (char_concat_A != char_concat_B) {
            char* empty = (char*)malloc(1 * sizeof(char));
            empty[0] = '\0';
            return empty;
        }
    }
    
    // 2. The Euclidean Exploit
    // If the strings commute, the divisor's length is EXACTLY the GCD of their lengths
    int gcd_len = get_gcd(len1, len2);
    
    // 3. Single, perfectly sized memory allocation
    char* result = (char*)malloc((gcd_len + 1) * sizeof(char));
    if (!result) return NULL; // Hardware safety check
    
    // Copy the prefix of length 'gcd_len' directly from str1
    memcpy(result, str1, gcd_len);
    result[gcd_len] = '\0'; // Secure with a null terminator
    
    return result;
}