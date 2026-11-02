#include <stdlib.h>
#include <string.h>

char* maskPII(char* s) {
    int len = 0;
    int at_idx = -1;
    int digit_count = 0;
    char last_four[4] = {0};

    // Pass 1: Categorize and capture metrics in a single sweep
    while (s[len] != '\0') {
        if (s[len] == '@') {
            at_idx = len;
        }
        else if (s[len] >= '0' && s[len] <= '9') {
            // Rolling buffer for the last 4 digits
            last_four[0] = last_four[1];
            last_four[1] = last_four[2];
            last_four[2] = last_four[3];
            last_four[3] = s[len];
            digit_count++;
        }
        len++;
    }

    if (at_idx != -1) {
        // --- EMAIL PATH ---
        int res_len = 7 + (len - at_idx); // First + 5 *s + Last + @ + Domain
        char* res = (char*)malloc(res_len + 1);
        
        res[0] = (s[0] >= 'A' && s[0] <= 'Z') ? s[0] + 32 : s[0];
        res[1] = '*'; res[2] = '*'; res[3] = '*'; res[4] = '*'; res[5] = '*';
        res[6] = (s[at_idx - 1] >= 'A' && s[at_idx - 1] <= 'Z') ? s[at_idx - 1] + 32 : s[at_idx - 1];

        int ptr = 7;
        for (int i = at_idx; i < len; i++) {
            res[ptr++] = (s[i] >= 'A' && s[i] <= 'Z') ? s[i] + 32 : s[i];
        }
        res[ptr] = '\0';
        return res;
        
    } else {
        // --- PHONE PATH ---
        char* country[] = {"", "+*-", "+**-", "+***-"};
        int c_len = digit_count - 10;
        char* prefix = country[c_len];
        int prefix_len = strlen(prefix);
        
        // Exact length: prefix + "***-***-" (8 chars) + last 4 + null terminator
        char* res = (char*)malloc(prefix_len + 8 + 4 + 1);
        int ptr = 0;
        
        for (int i = 0; i < prefix_len; i++) res[ptr++] = prefix[i];
        
        char* mid = "***-***-";
        for (int i = 0; i < 8; i++) res[ptr++] = mid[i];
        
        for (int i = 0; i < 4; i++) res[ptr++] = last_four[i];
        
        res[ptr] = '\0';
        return res;
    }
}