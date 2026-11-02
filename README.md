<div align="center">

# C-Tutorials 💻

### High-Performance Systems Programming & Algorithmic Solutions in Pure C

<p align="center">
  <em>Curated LeetCode patterns, custom systems data structures, and deterministic algorithmic problem-solving developed through deep technical practice in Gemini sessions.</em>
</p>

[![C11](https://img.shields.io/badge/Language-C11-00599C?style=flat-square&logo=c)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))
[![Compiler](https://img.shields.io/badge/Compiler-Clang%20%2F%20GCC-green?style=flat-square)](https://clang.llvm.org)
[![Sanitizer](https://img.shields.io/badge/Sanitizer-UBSan%20%26%20Leaks-blueviolet?style=flat-square)](https://clang.llvm.org)
[![Zero Leaks](https://img.shields.io/badge/Memory-0%20Leaks%20Verified-brightgreen?style=flat-square)](https://github.com/jyotirawattech/C-Tutorials)

</div>

---

## 🎯 Motivation & Engineering Philosophy

Solving algorithmic problems in high-level languages often masks the true mechanics of computer systems. In Python, Java, or modern C++, associative lookups and dynamic arrays are hidden behind abstractions like `std::unordered_map` or `vector`.

In **pure C (C11)** systems programming:
1. **No Built-in Containers**: You build hash tables, doubly linked lists, tries, ring buffers, and trees directly on bare pointers and memory blocks.
2. **Explicit Memory Budgets**: Every byte allocated via `malloc()` or `calloc()` must have a mathematically provable, leak-free deallocation path.
3. **Cache Line & Hardware Efficiency**: Algorithms prioritize cache locality, minimize pointer indirection, and prefer stack buffers over heap churn where applicable.
4. **Deterministic Validation**: Every solution in this repository is paired with an automated test runner and verified for memory safety (`leaks`, `UBSan`, `ASan`).

---

## 📚 Problem Catalog & Patterns

| # | Problem | Category | Core Pattern & Data Structure | Time | Space | Verification |
| :-: | :--- | :--- | :--- | :-: | :-: | :-: |
| **0001** | [**Two Sum**](01_arrays_and_hashing/0001_two_sum) | Arrays & Hashing | Custom Hash Table with Separate Chaining | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | `0 leaks` ✅ |
| **0003** | [**Longest Substring Without Repeating Characters**](02_two_pointers_and_strings/0003_longest_substring_without_repeating_characters) | Two Pointers & Strings | Sliding Window + Direct ASCII Indexing (Zero Heap) | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | `0 leaks` ✅ |
| **0020** | [**Valid Parentheses**](02_two_pointers_and_strings/0020_valid_parentheses) | Strings & Stack | Bounded LIFO Stack with Early Exit | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | `0 leaks` ✅ |
| **0021** | [**Merge Two Sorted Lists**](03_linked_lists/0021_merge_two_sorted_lists) | Linked Lists | Sentinel Stack Dummy Node & In-Place Splicing | $\mathcal{O}(M+N)$ | $\mathcal{O}(1)$ | `0 leaks` ✅ |
| **0136** | [**Single Number**](06_binary_search_and_bits/0136_single_number) | Bit Manipulation | Bitwise XOR Streaming Accumulator | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | `0 leaks` ✅ |
| **0141** | [**Linked List Cycle**](03_linked_lists/0141_linked_list_cycle) | Linked Lists | Floyd's Cycle-Finding Algorithm (Tortoise & Hare) | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | `0 leaks` ✅ |
| **0146** | [**LRU Cache**](05_systems_data_structures/0146_lru_cache) | Systems Data Structures | Doubly Linked List with Sentinels + Hash Table | $\mathcal{O}(1)$ | $\mathcal{O}(K)$ | `0 leaks` ✅ |
| **0206** | [**Reverse Linked List**](03_linked_lists/0206_reverse_linked_list) | Linked Lists | In-Place Three-Pointer Rewiring | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | `0 leaks` ✅ |
| **0208** | [**Implement Trie (Prefix Tree)**](04_trees_and_graphs/0208_implement_trie) | Trees & Routing Tables | 26-ary Trie with Direct Indexing & Post-Order Teardown | $\mathcal{O}(L)$ | $\mathcal{O}(N \times \Sigma)$ | `0 leaks` ✅ |
| **0226** | [**Invert Binary Tree**](04_trees_and_graphs/0226_invert_binary_tree) | Trees & Graphs | Recursive Child Pointer Swapping | $\mathcal{O}(N)$ | $\mathcal{O}(H)$ | `0 leaks` ✅ |
| **0704** | [**Binary Search**](06_binary_search_and_bits/0704_binary_search) | Binary Search | Overflow-Safe Midpoint Calculation `low + (high-low)/2` | $\mathcal{O}(\log N)$ | $\mathcal{O}(1)$ | `0 leaks` ✅ |

---

## 🛠️ Repository Layout

```text
C-Tutorials/
├── Makefile                               # Unified test runner and build orchestrator
├── README.md                              # Repository overview and problem matrix
├── scripts/
│   └── run_tests.sh                       # Automated test execution and leak verifier
├── 01_arrays_and_hashing/
│   └── 0001_two_sum/
├── 02_two_pointers_and_strings/
│   ├── 0003_longest_substring_without_repeating_characters/
│   └── 0020_valid_parentheses/
├── 03_linked_lists/
│   ├── 0021_merge_two_sorted_lists/
│   ├── 0141_linked_list_cycle/
│   └── 0206_reverse_linked_list/
├── 04_trees_and_graphs/
│   ├── 0208_implement_trie/
│   └── 0226_invert_binary_tree/
├── 05_systems_data_structures/
│   └── 0146_lru_cache/
└── 06_binary_search_and_bits/
    ├── 0136_single_number/
    └── 0704_binary_search/
```

---

## 🚀 Building & Running Tests

### Run All Tests
To compile every solution with strict warnings (`-Wall -Wextra -Werror -pedantic -std=c11 -fsanitize=undefined`) and verify zero memory leaks:

```bash
make test
```

Expected output:
```text
================================================================
  C-Tutorials: LeetCode in C Verification Suite
  Compiler: Apple clang version 17.0.0
================================================================
[1] Compiling: 0001_two_sum
    Executing & verifying memory safety...
    ✅ PASSED (0 leaks verified)
...
[11] Compiling: 0704_binary_search
    Executing & verifying memory safety...
    ✅ PASSED (0 leaks verified)
================================================================
  Summary: 11 / 11 Passed (0 Failed)
================================================================
```

---

<div align="center">
  <sub>Maintained by <a href="https://github.com/jyotirawattech">Jyoti Rawat</a> &bull; Systems & Platform Software Engineer &bull; Cisco</sub>
</div>
