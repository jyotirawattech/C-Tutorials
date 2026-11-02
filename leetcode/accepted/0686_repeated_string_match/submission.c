#include <string.h>
#include <stdlib.h>

int repeatedStringMatch(char * a, char * b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    
    int repeats = len_b / len_a;
    if (len_b % len_a != 0) repeats++;
    
    // Allocate max memory: (repeats + 1) * len_a + 1 for null terminator
    int max_bytes = (repeats + 1) * len_a;
    char *buffer = (char *)malloc(max_bytes + 1);
    if (!buffer) return -1;
    
    char *ptr = buffer;
    
    // Fast SIMD memory copy
    for (int i = 0; i < repeats; i++) {
        memcpy(ptr, a, len_a);
        ptr += len_a;
    }
    *ptr = '\0'; // Manually null terminate
    
    if (strstr(buffer, b) != NULL) {
        free(buffer);
        return repeats;
    }
    
    // Add the +1 overflow bound
    memcpy(ptr, a, len_a);
    ptr += len_a;
    *ptr = '\0';
    
    if (strstr(buffer, b) != NULL) {
        free(buffer);
        return repeats + 1;
    }
    
    free(buffer);
    return -1;
}