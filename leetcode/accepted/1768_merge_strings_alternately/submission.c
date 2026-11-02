#include <stdlib.h>
#include <string.h>

char * mergeAlternately(char * word1, char * word2) {
    // 1. Measure the exact memory boundaries
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    int total_len = len1 + len2;
    
    // 2. Exact Memory Allocation (The +1 is critical for the '\0' terminator)
    char* merged = (char*)malloc((total_len + 1) * sizeof(char));
    if (!merged) return NULL; // Hardware safety check
    
    int i = 0; // Read pointer for word1
    int j = 0; // Read pointer for word2
    int k = 0; // Write pointer for merged buffer
    
    // 3. The Weave State Machine
    while (i < len1 && j < len2) {
        merged[k++] = word1[i++];
        merged[k++] = word2[j++];
    }
    
    // 4. Drain the remaining buffers 
    // (Only one of these loops will execute depending on which string was longer)
    while (i < len1) {
        merged[k++] = word1[i++];
    }
    while (j < len2) {
        merged[k++] = word2[j++];
    }
    
    // 5. Secure the memory block with a null terminator
    merged[k] = '\0';
    
    return merged;
}