#include <stdlib.h>

char* licenseKeyFormatting(char* s, int k) {
    // 1. Find string length and count valid characters
    int len = 0;
    int valid_count = 0;
    
    while (s[len] != '\0') {
        if (s[len] != '-') {
            valid_count++;
        }
        len++;
    }
    
    if (valid_count == 0) {
        char* empty_str = (char*)malloc(1);
        empty_str[0] = '\0';
        return empty_str;
    }
    
    // Calculate new length and allocate exactly
    int dash_count = (valid_count - 1) / k;
    int new_len = valid_count + dash_count;
    
    char* res = (char*)malloc(new_len + 1);
    res[new_len] = '\0'; // Null terminator
    
    int ptr = new_len - 1;
    int chunk = 0;
    
    // 2. Fill backwards
    for (int i = len - 1; i >= 0; i--) {
        if (s[i] != '-') {
            if (chunk == k) {
                res[ptr--] = '-';
                chunk = 0;
            }
            
            char c = s[i];
            if (c >= 'a' && c <= 'z') {
                c -= 32; // Fast upper
            }
            
            res[ptr--] = c;
            chunk++;
        }
    }
    
    return res;
}