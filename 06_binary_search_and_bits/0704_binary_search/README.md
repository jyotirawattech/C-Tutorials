# LeetCode 0704: Binary Search

- **Difficulty**: Easy
- **Category**: Binary Search & Memory Addressing
- **Language**: C (C11)

## Problem Statement

Given an array of integers `nums` which is sorted in ascending order, and an integer `target`, write a function to search `target` in `nums`. If `target` exists, then return its index. Otherwise, return `-1`.

You must write an algorithm with $\mathcal{O}(\log n)$ runtime complexity.

## Systems Engineering Analysis

1. **Integer Overflow Prevention**: In low-level systems programming, computing midpoint as `(low + high) / 2` can cause integer overflow if `low + high > INT_MAX` (2,147,483,647), leading to negative indices and memory segfaults (`EXC_BAD_ACCESS`). Using `low + (high - low) / 2` guarantees overflow safety.
2. **Cache-Line Prefetching**: Contiguous arrays benefit from hardware prefetchers reading cache lines (typically 64 bytes) ahead of time.

## Complexity

- **Time Complexity**: $\mathcal{O}(\log N)$ logarithmic search iterations.
- **Space Complexity**: $\mathcal{O}(1)$ constant stack memory.

## Compilation & Verification

```bash
clang -Wall -Wextra -Werror -pedantic -std=c11 -fsanitize=undefined solution.c -o solution
./solution
```
