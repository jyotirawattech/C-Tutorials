// The Recursive Backtracking State Machine
void backtrack(int n, int open_count, int close_count, char* current_str, int index, char** result, int* returnSize) {
    // 1. Base Case (The Goal State)
    // If we have placed 'n' open and 'n' close brackets, the string is complete.
    if (open_count == n && close_count == n) {
        current_str[index] = '\0'; // Secure with a null terminator
        
        // Allocate heap memory for this specific valid combination
        result[*returnSize] = (char*)malloc((2 * n + 1) * sizeof(char));
        strcpy(result[*returnSize], current_str);
        
        (*returnSize)++;
        return;
    }

    // 2. Branch A: Add an Open Parenthesis
    // We can ALWAYS add an open parenthesis as long as we haven't hit our limit 'n'
    if (open_count < n) {
        current_str[index] = '(';
        // Recurse deeper into the Call Stack
        backtrack(n, open_count + 1, close_count, current_str, index + 1, result, returnSize);
    }

    // 3. Branch B: Add a Close Parenthesis (The Pruning Condition)
    // We can ONLY add a close parenthesis if it mathematically closes an existing open one.
    // If close_count >= open_count, adding ')' would instantly invalidate the string, so we prune that branch.
    if (close_count < open_count) {
        current_str[index] = ')';
        // Recurse deeper into the Call Stack
        backtrack(n, open_count, close_count + 1, current_str, index + 1, result, returnSize);
    }
}

char** generateParenthesis(int n, int* returnSize) {
    // HARDWARE EXPLOIT: Constraint n <= 8
    // The maximum number of valid combinations for n=8 is defined by the 8th Catalan Number (1430).
    // We allocate a perfectly safe buffer of 1500 to hold our string pointers.
    int max_combinations = 1500; 
    char** result = (char**)malloc(max_combinations * sizeof(char*));
    *returnSize = 0;

    // Allocate a single temporary buffer to act as our working string during recursion.
    // Length is 2*n (brackets) + 1 (null terminator)
    char* current_str = (char*)malloc((2 * n + 1) * sizeof(char));
    
    // Deploy the recursive state machine
    backtrack(n, 0, 0, current_str, 0, result, returnSize);
    
    // Clean up our temporary working buffer
    free(current_str);
    
    return result;
}