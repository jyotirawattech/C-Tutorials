#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool rotateString(char * s, char * goal) {
    int lenS = strlen(s);
    int lenG = strlen(goal);
    
    // Step 1: Length check constraint
    if (lenS != lenG) {
        return false;
    }
    
    // Step 2: Allocate exact memory for the doubled buffer (+1 for null terminator)
    char *doubled = (char *)malloc((2 * lenS + 1) * sizeof(char));
    if (!doubled) return false; // Hardware safety check
    
    // Step 3: Fast concatenation bypassing strcat
    strcpy(doubled, s);
    strcpy(doubled + lenS, s);
    
    // Step 4: Substring search
    bool found = (strstr(doubled, goal) != NULL);
    
    // Step 5: Prevent memory leaks
    free(doubled);
    
    return found;
}