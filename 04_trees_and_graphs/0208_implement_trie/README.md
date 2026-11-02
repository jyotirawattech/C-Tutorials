# LeetCode 0208: Implement Trie (Prefix Tree)

- **Difficulty**: Medium
- **Category**: Trees & Networking Prefix Tables
- **Language**: C (C11)

## Problem Statement

A **trie** (pronounced as "try") or **prefix tree** is a tree data structure used to efficiently store and retrieve keys in a dataset of strings.

Implement the `Trie` class:
- `Trie()`: Initializes the trie object.
- `void insert(String word)`: Inserts string `word` into the trie.
- `boolean search(String word)`: Returns `true` if `word` is in the trie.
- `boolean startsWith(String prefix)`: Returns `true` if there is a previously inserted string `word` that has the prefix `prefix`.

## Systems Engineering Analysis

Tries are ubiquitous in networking routing tables (Longest Prefix Match / Radix trees in IP forwarding engines), fast autocomplete, and packet classification filters.
1. **Direct Pointer Indexing**: Each node holds an array of 26 pointers (`struct Trie* children[26]`). Character offset calculation (`word[i] - 'a'`) provides branch-free $\mathcal{O}(1)$ child lookup.
2. **Deterministic Teardown**: Because tries are multi-way branching trees, `trieFree` performs a post-order recursive traversal across all 26 pointer branches, eliminating dangling node memory.

## Complexity

- **Time Complexity**: $\mathcal{O}(L)$ for `insert`, `search`, and `startsWith`, where $L$ is the string length.
- **Space Complexity**: $\mathcal{O}(N \times \Sigma)$ where $N$ is total characters and $\Sigma = 26$.

## Compilation & Verification

```bash
clang -Wall -Wextra -Werror -pedantic -std=c11 -fsanitize=undefined solution.c -o solution
./solution
```
