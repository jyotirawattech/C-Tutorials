# LeetCode 0001: Two Sum

- **Difficulty**: Easy
- **Category**: Arrays & Hashing
- **Language**: C (C11)

## Problem Statement

Given an array of integers `nums` and an integer `target`, return indices of the two numbers such that they add up to `target`.

You may assume that each input would have *exactly one solution*, and you may not use the same element twice. You can return the answer in any order.

## Systems Engineering Analysis

In high-level languages (Python, Java, C++), developers rely on built-in associative containers (`std::unordered_map`, `dict`). In low-level C systems programming:
1. **No Standard Hash Map**: Standard C lacks a generic hash table in `libc`.
2. **Explicit Memory Allocation**: Dynamic memory must be allocated for bucket heads and collision nodes.
3. **Collision Strategy**: We implement separate chaining with linked list nodes.
4. **Leak Prevention**: When a target pair is found (early return), all dynamically allocated bucket nodes and hash map headers must be cleanly freed before returning.

## Complexity

- **Time Complexity**: $\mathcal{O}(N)$ average, $\mathcal{O}(N^2)$ worst-case on total hash collisions.
- **Space Complexity**: $\mathcal{O}(N)$ memory allocated for hash nodes.

## Compilation & Verification

Compile with AddressSanitizer and UndefinedBehaviorSanitizer enabled:

```bash
clang -Wall -Wextra -Werror -pedantic -std=c11 -fsanitize=address,undefined solution.c -o solution
./solution
```
