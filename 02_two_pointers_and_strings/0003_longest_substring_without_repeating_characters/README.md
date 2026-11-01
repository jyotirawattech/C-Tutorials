# LeetCode 0003: Longest Substring Without Repeating Characters

- **Difficulty**: Medium
- **Category**: Two Pointers & Sliding Window
- **Language**: C (C11)

## Problem Statement

Given a string `s`, find the length of the **longest substring** without repeating characters.

## Systems Engineering Analysis

In systems and embedded programming, heap allocations (`malloc`) introduce latency variability, heap fragmentation, and potential allocation failures under low-memory constraints.
1. **Zero Heap Allocation**: We avoid dynamic memory by allocating a fixed 256-integer array directly on the thread stack to represent all possible ASCII byte values (`0..255`).
2. **Direct Indexing**: Fast direct lookup via `(unsigned char)s[i]` indexing provides $O(1)$ character lookup without hash collisions.
3. **Sliding Window Optimization**: Rather than contracting the window incrementally by one index at a time, we jump `window_start` directly past the previous occurrence of the colliding character.

## Complexity

- **Time Complexity**: $\mathcal{O}(N)$ where $N$ is the string length (linear single-pass).
- **Space Complexity**: $\mathcal{O}(1)$ deterministic constant stack space (256 integers = 1024 bytes).

## Compilation & Verification

```bash
clang -Wall -Wextra -Werror -pedantic -std=c11 -fsanitize=address,undefined solution.c -o solution
./solution
```
