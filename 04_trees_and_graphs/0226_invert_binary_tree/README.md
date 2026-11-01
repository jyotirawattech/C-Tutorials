# LeetCode 0226: Invert Binary Tree

- **Difficulty**: Easy
- **Category**: Trees & Graphs
- **Language**: C (C11)

## Problem Statement

Given the `root` of a binary tree, invert the tree, and return *its root*.

## Systems Engineering Analysis

Binary trees represent core systems concepts (page tables, radix trees, abstract syntax trees, hierarchical schedulers).
1. **Recursive Stack Frame Budgeting**: Recursive descent relies on the process stack. In embedded systems or kernel contexts where thread stack sizes can be constrained (e.g., 8KB or 16KB), unbounded tree depth risk stack overflow (`EXC_BAD_ACCESS`).
2. **Atomic Pointer Swapping**: The inversion is accomplished by swapping the 64-bit address references of the `left` and `right` subtrees and recursing into the children.
3. **Deterministic Freeing**: To ensure zero memory leaks, post-order traversal (`free_tree`) frees leaf nodes before their parent pointer is destroyed.

## Complexity

- **Time Complexity**: $\mathcal{O}(N)$ where $N$ is the total number of nodes (each node visited once).
- **Space Complexity**: $\mathcal{O}(H)$ call stack space where $H$ is the tree height ($\mathcal{O}(\log N)$ for balanced trees, $\mathcal{O}(N)$ for skewed trees).

## Compilation & Verification

```bash
clang -Wall -Wextra -Werror -pedantic -std=c11 -fsanitize=address,undefined solution.c -o solution
./solution
```
