# LeetCode 0206: Reverse Linked List

- **Difficulty**: Easy
- **Category**: Linked Lists & Pointer Manipulation
- **Language**: C (C11)

## Problem Statement

Given the `head` of a singly linked list, reverse the list, and return *the reversed list*.

## Systems Engineering Analysis

Linked list reversal is a cornerstone of kernel and systems data structures (e.g., free lists, thread wait queues, network buffer rings).
1. **Pointer Rewiring Without Heap Churn**: In C, we do not copy values or allocate new wrapper nodes. We mutate the `next` pointer references directly in place.
2. **Three-Pointer Invariant**: At each iteration, three references are preserved:
   - `prev`: Points to the already-reversed prefix.
   - `curr`: The active node whose pointer is being rewired.
   - `next_node`: Caches `curr->next` to prevent losing the remaining list tail when rewiring.
3. **Cache Line Considerations**: Singly linked lists exhibit poor spatial cache locality compared to contiguous arrays. Reversal in-place minimizes cache invalidation overhead.

## Complexity

- **Time Complexity**: $\mathcal{O}(N)$ where $N$ is the number of nodes in the list.
- **Space Complexity**: $\mathcal{O}(1)$ auxiliary memory (only 3 pointer variables on the stack).

## Compilation & Verification

```bash
clang -Wall -Wextra -Werror -pedantic -std=c11 -fsanitize=address,undefined solution.c -o solution
./solution
```
