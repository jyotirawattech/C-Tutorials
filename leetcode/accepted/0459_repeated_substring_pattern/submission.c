#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool repeatedSubstringPattern(char * s) {
    int n = strlen(s);
    if (n <= 1) return false;
    
    // Allocate LPS array initialized to 0
    int* lps = (int*)calloc(n, sizeof(int));
    if (!lps) return false;
    
    int len = 0;
    int i = 1;
    
    // Build the KMP LPS Array
    while (i < n) {
        if (s[i] == s[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1]; // Rollback
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    
    int lps_last = lps[n - 1];
    free(lps);
    
    // Mathematical evaluation of periodicity
    return (lps_last > 0 && n % (n - lps_last) == 0);
}