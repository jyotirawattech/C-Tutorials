# LeetCode 0020: Valid Parentheses

- **Difficulty**: Easy
- **Category**: Strings & Stack
- **Language**: C (C11)

## Problem Statement

Given a string `s` containing just the characters `'('`, `')'`, `'{'`, `'}'`, `'['` and `']'`, determine if the input string is valid.

## Systems Engineering Analysis

1. **Stack Implementation in C**: C lacks `std::stack`. We implement an array-based stack bounded by the input length $\text{len}(s)$.
2. **Early Exit Guard**: An odd string length immediately violates balance and exits in $\mathcal{O}(1)$ before allocating heap buffers.
3. **Deterministic Memory Cleanup**: Any mismatch during traversal cleanly frees the allocated stack buffer before returning `false`, eliminating early-exit leaks.

## Complexity

- **Time Complexity**: $\mathcal{O}(N)$ where $N$ is the length of the string.
- **Space Complexity**: $\mathcal{O}(N)$ memory allocated for the stack.

## Compilation & Verification

```bash
clang -Wall -Wextra -Werror -pedantic -std=c11 -fsanitize=undefined solution.c -o solution
./solution
```
