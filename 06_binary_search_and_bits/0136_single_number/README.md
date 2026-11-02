# LeetCode 0136: Single Number

- **Difficulty**: Easy
- **Category**: Bit Manipulation & Systems Math
- **Language**: C (C11)

## Problem Statement

Given a **non-empty** array of integers `nums`, every element appears twice except for one. Find that single one.

You must implement a solution with a linear runtime complexity and use only constant extra space.

## Systems Engineering Analysis

1. **Hardware-Level Bitwise Operator**: In assembly and CPU microarchitectures, bitwise XOR is a single-cycle instruction (e.g. `eor` on ARM64, `xor` on x86_64).
2. **Zero Register Spilling**: The accumulator variable `unique` remains in a CPU register throughout the loop, avoiding stack frame reads/writes.
3. **Cache Line Streaming**: Contiguous memory access allows the CPU L1 data cache to achieve maximum throughput with sequential prefetching.

## Complexity

- **Time Complexity**: $\mathcal{O}(N)$ single linear pass.
- **Space Complexity**: $\mathcal{O}(1)$ single register / zero allocations.

## Compilation & Verification

```bash
clang -Wall -Wextra -Werror -pedantic -std=c11 -fsanitize=undefined solution.c -o solution
./solution
```
