#include <stdbool.h>

bool detectCapitalUse(char * word) {
    // If the string is empty or only 1 character, it's valid
    if (!word[0] || !word[1]) return true;

    bool first_upper = (word[0] >= 'A' && word[0] <= 'Z');
    bool second_upper = (word[1] >= 'A' && word[1] <= 'Z');

    // Instant failure on "aB"
    if (!first_upper && second_upper) return false;

    bool expect_upper = first_upper && second_upper;

    // Advance pointer to the 3rd character
    char* ptr = word + 2;

    while (*ptr != '\0') {
        bool is_upper = (*ptr >= 'A' && *ptr <= 'Z');
        if (is_upper != expect_upper) {
            return false;
        }
        ptr++; // Walk the pointer forward
    }

    return true;
}