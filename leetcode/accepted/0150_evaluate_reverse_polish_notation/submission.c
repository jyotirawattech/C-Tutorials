#include <stdlib.h>

int evalRPN(char ** tokens, int tokensSize) {
    // Allocate raw contiguous memory.
    int* stack = (int*)malloc(sizeof(int) * tokensSize);
    int top = -1; // Stack pointer
    
    for (int i = 0; i < tokensSize; i++) {
        char* t = tokens[i];
        
        // Elite String Parsing: 
        // If the second character is the null terminator '\0', 
        // AND the first character is not a number, it IS an operator.
        // This flawlessly differentiates the "-" operator from "-11".
        if (t[1] == '\0' && (t[0] == '+' || t[0] == '-' || t[0] == '*' || t[0] == '/')) {
            int b = stack[top--];
            int a = stack[top--];
            
            if (t[0] == '+') stack[++top] = a + b;
            else if (t[0] == '-') stack[++top] = a - b;
            else if (t[0] == '*') stack[++top] = a * b;
            else if (t[0] == '/') stack[++top] = a / b;
        } else {
            // It's a number. Convert and push.
            stack[++top] = atoi(t);
        }
    }
    
    int result = stack[top];
    free(stack);
    
    return result;
}