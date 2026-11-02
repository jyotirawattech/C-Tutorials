# LeetCode 0021: Merge Two Sorted Lists

- **Difficulty**: Easy
- **Category**: Linked Lists
- **Language**: C (C11)

## Problem Statement

You are given the heads of two sorted linked lists `list1` and `list2`.

Merge the two lists into one **sorted** list. The list should be made by splicing together the nodes of the first two lists. Return the head of the merged linked list.

## Systems Engineering Analysis

1. **Stack-Allocated Sentinel Node**: Rather than checking whether the head pointer is uninitialized on the first iteration (`if (!head) head = ...`), we declare `struct ListNode dummy;` directly on the stack. The tail pointer advances from `&dummy`.
2. **Zero Heap Allocation**: No calls to `malloc()` are needed. Pointers from the existing input lists are re-linked directly, eliminating memory churn and page allocation latency.
3. **Tail Splicing**: Once either list is exhausted, the remaining elements are attached with a single $\mathcal{O}(1)$ pointer assignment: `tail->next = (list1 != NULL) ? list1 : list2;`.

## Complexity

- **Time Complexity**: $\mathcal{O}(M + N)$ where $M$ and $N$ are list lengths.
- **Space Complexity**: $\mathcal{O}(1)$ auxiliary space.

## Compilation & Verification

```bash
clang -Wall -Wextra -Werror -pedantic -std=c11 -fsanitize=undefined solution.c -o solution
./solution
```
