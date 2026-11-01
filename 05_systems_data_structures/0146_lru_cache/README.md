# LeetCode 0146: LRU Cache

- **Difficulty**: Medium
- **Category**: Systems Data Structures & Memory Management
- **Language**: C (C11)

## Problem Statement

Design a data structure that follows the constraints of a **Least Recently Used (LRU) cache**.

Implement the `LRUCache` class:
- `LRUCache(int capacity)`: Initialize the LRU cache with positive size `capacity`.
- `int get(int key)`: Return the value of the `key` if the key exists, otherwise return `-1`.
- `void put(int key, int value)`: Update the value of the `key` if the `key` exists. Otherwise, add the `key-value` pair to the cache. If the number of keys exceeds the `capacity` from this operation, **evict** the least recently used key.

The functions `get` and `put` must each run in $\mathcal{O}(1)$ average time complexity.

## Systems Engineering Analysis

LRU caching is the foundational algorithm for kernel buffer caches (e.g. Linux page cache), translation lookaside buffers (TLB), and database query caches.
1. **Doubly Linked List with Sentinels**: Dummy `head` and `tail` nodes eliminate boundary conditions (`if (node == head)`) on insertion and removal, resulting in branch-free $O(1)$ node splicing.
2. **Hash Table with Separate Chaining**: In C, we pair the linked list with a dynamic hash map pointing directly to the `DListNode*` memory addresses.
3. **Deterministic Eviction**: When `size == capacity`, the node immediately preceding the dummy tail (`tail->prev`) is unlinked, its hash entry is removed, and its memory is reclaimed via `free()`.
4. **Zero-Leak Teardown**: `lruCacheFree` walks both the doubly linked list and all hash bucket chains to ensure full memory deallocation.

## Complexity

- **Time Complexity**:
  - `get(key)`: $\mathcal{O}(1)$
  - `put(key, value)`: $\mathcal{O}(1)$
- **Space Complexity**: $\mathcal{O}(\text{capacity})$ strictly bounded memory footprint.

## Compilation & Verification

```bash
clang -Wall -Wextra -Werror -pedantic -std=c11 -fsanitize=address,undefined solution.c -o solution
./solution
```
