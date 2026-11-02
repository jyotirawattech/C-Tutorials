# LeetCode 0141: Linked List Cycle

- **Difficulty**: Easy
- **Category**: Linked Lists & Two Pointers
- **Language**: C (C11)

## Problem Statement

Given `head`, the head of a linked list, determine if the linked list has a cycle in it.

Return `true` if there is some cycle in the linked list. Otherwise, return `false`.

## Systems Engineering Analysis

Cycle detection is essential in kernel memory subsystems to prevent infinite loops in process lists, scheduling wait queues, and deadlocked dependency graphs.
1. **Pointer Speed Differential**: By advancing pointers at speeds $\nu_1 = 1$ and $\nu_2 = 2$, the relative distance closes by 1 node per iteration, guaranteeing a cycle is caught in $\mathcal{O}(N)$ without hashing node memory addresses.
2. **Zero Memory Allocation**: Avoids building a hash set of pointer addresses, maintaining a deterministic $\mathcal{O}(1)$ space profile.
3. **Safe Memory Deallocation**: Cyclic data structures cannot be freed with standard traversal routines without first detecting and breaking the cyclic back-pointer.

## Complexity

- **Time Complexity**: $\mathcal{O}(N)$ where $N$ is the number of nodes.
- **Space Complexity**: $\mathcal{O}(1)$ constant memory overhead.

## Compilation & Verification

```bash
clang -Wall -Wextra -Werror -pedantic -std=c11 -fsanitize=undefined solution.c -o solution
./solution
```
