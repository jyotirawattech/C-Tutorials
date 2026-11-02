<div align="center">

# C-Tutorials 💻

### C11 algorithms, memory ownership and tested data structures

<p align="center">
  <em>Practice solutions with local explanations and standalone tests. Original practice dates and platform acceptance remain unverified unless an entry records actual evidence.</em>
</p>

[![C11](https://img.shields.io/badge/Language-C11-00599C?style=flat-square&logo=c)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))
[![Compiler](https://img.shields.io/badge/Compiler-Clang%20%2F%20GCC-green?style=flat-square)](https://clang.llvm.org)
[![Sanitizer](https://img.shields.io/badge/Checks-UBSan%20%2B%20optional%20ASan-blueviolet?style=flat-square)](https://clang.llvm.org)


</div>

---

## 🎯 Motivation & Engineering Philosophy

Solving algorithmic problems in high-level languages often masks the true mechanics of computer systems. In Python, Java, or modern C++, associative lookups and dynamic arrays are hidden behind abstractions like `std::unordered_map` or `vector`.

In **pure C (C11)** systems programming:
1. **No Built-in Containers**: You build hash tables, doubly linked lists, tries, ring buffers, and trees directly on bare pointers and memory blocks.
2. **Explicit Memory Ownership**: Explain allocation, ownership and cleanup, then exercise relevant paths in tests.
3. **Reasoned Trade-offs**: Explain the data-structure choice and its time/space assumptions; performance measurements require a separate benchmark.
4. **Bounded Validation**: Each solution has standalone assertions. The runner enables fail-fast UBSan, supports optional ASan, and reports separate leak-detector checks or skips. Passing exercised cases does not prove memory safety for every input.

---

## 📚 Problem Catalog & Patterns

| # | Problem | Category | Core Pattern & Data Structure | Time | Space | Verification |
| :-: | :--- | :--- | :--- | :-: | :-: | :-: |
| **0001** | [**Two Sum**](01_arrays_and_hashing/0001_two_sum) | Arrays & Hashing | Custom Hash Table with Separate Chaining | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | Local assertions |
| **0003** | [**Longest Substring Without Repeating Characters**](02_two_pointers_and_strings/0003_longest_substring_without_repeating_characters) | Two Pointers & Strings | Sliding Window + Direct ASCII Indexing (Zero Heap) | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | Local assertions |
| **0020** | [**Valid Parentheses**](02_two_pointers_and_strings/0020_valid_parentheses) | Strings & Stack | Bounded LIFO Stack with Early Exit | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | Local assertions |
| **0021** | [**Merge Two Sorted Lists**](03_linked_lists/0021_merge_two_sorted_lists) | Linked Lists | Sentinel Stack Dummy Node & In-Place Splicing | $\mathcal{O}(M+N)$ | $\mathcal{O}(1)$ | Local assertions |
| **0121** | [**Best Time to Buy and Sell Stock**](01_arrays_and_hashing/0121_best_time_to_buy_and_sell_stock) | Arrays | Running Prefix Minimum | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | Accepted source + local assertions/oracle |
| **0136** | [**Single Number**](06_binary_search_and_bits/0136_single_number) | Bit Manipulation | Bitwise XOR Streaming Accumulator | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | Local assertions |
| **0141** | [**Linked List Cycle**](03_linked_lists/0141_linked_list_cycle) | Linked Lists | Floyd's Cycle-Finding Algorithm (Tortoise & Hare) | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | Local assertions |
| **0146** | [**LRU Cache**](05_systems_data_structures/0146_lru_cache) | Systems Data Structures | Doubly Linked List with Sentinels + Hash Table | $\mathcal{O}(1)$ | $\mathcal{O}(K)$ | Local assertions |
| **0206** | [**Reverse Linked List**](03_linked_lists/0206_reverse_linked_list) | Linked Lists | In-Place Three-Pointer Rewiring | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | Local assertions |
| **0208** | [**Implement Trie (Prefix Tree)**](04_trees_and_graphs/0208_implement_trie) | Trees & Routing Tables | 26-ary Trie with Direct Indexing & Post-Order Teardown | $\mathcal{O}(L)$ | $\mathcal{O}(N \times \Sigma)$ | Local assertions |
| **0226** | [**Invert Binary Tree**](04_trees_and_graphs/0226_invert_binary_tree) | Trees & Graphs | Recursive Child Pointer Swapping | $\mathcal{O}(N)$ | $\mathcal{O}(H)$ | Local assertions |
| **0704** | [**Binary Search**](06_binary_search_and_bits/0704_binary_search) | Binary Search | Overflow-Safe Midpoint Calculation `low + (high-low)/2` | $\mathcal{O}(\log N)$ | $\mathcal{O}(1)$ | Local assertions |

---

## 🛠️ Repository Layout

```text
C-Tutorials/
├── Makefile                               # Unified test runner and build orchestrator
├── README.md                              # Repository overview and problem matrix
├── scripts/
│   └── run_tests.sh                       # Test execution and detector result reporting
├── 01_arrays_and_hashing/
│   ├── 0001_two_sum/
│   └── 0121_best_time_to_buy_and_sell_stock/
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

## Building and running tests

Requires Bash, Make, and a C11 compiler with UBSan support (Clang is the default).
No external problem-platform access or package download is needed.

```bash
make test
```

This runs the runner's negative regressions, then compiles and executes the twelve
existing solutions with strict warnings and fail-fast UBSan. If Apple's `leaks`
tool is present, it runs a separate plain binary. Any nonzero leak-detector exit
fails; a missing detector is explicitly skipped and is not a leak-free result.

On a supported AddressSanitizer runtime:

```bash
SANITIZERS=address,undefined make test
```

ASan is a separate mode; do not infer that it ran from a default test pass.
`LEAK_CHECK=required make test` requires the separate detector;
`LEAK_CHECK=skip make test` explicitly skips it while keeping sanitizer checks.
Some legacy solution messages say “zero leaks”; only the runner's actual detector
result establishes which check executed.

The local candidate was checked on 2 November 2026 using Apple Clang 17 on
macOS 27.2: all eleven solutions passed with UBSan, and all eleven `leaks`
invocations exited successfully. The detector printed restricted-process notices;
these observations are bounded local checks, not a universal no-leak guarantee.
The optional ASan runtime hung on this host and was terminated without claiming
a pass. CI is configured for ASan plus UBSan on Linux and UBSan on macOS;
check the [actual workflow results](https://github.com/jyotirawattech/C-Tutorials/actions)
for the revision being reviewed.

The 0121 archive was additionally validated locally on 2 November 2026: all twelve
solution harnesses and six runner regressions passed with fail-fast UBSan. Its
tests include eleven fixed cases, 1024 deterministic comparisons with a brute-force
oracle, and a maximum-length input. Twelve separate `leaks` invocations returned
zero with the same restricted-process notices; ASan was not run for this addition.

## Daily practice, notes and provenance

Use the [daily workflow](docs/daily-practice.md) and
[entry template](docs/practice-entry-template.md) for new solutions and meaningful
improvements. Each entry records approach, complexity, edge cases, actual test
results, assistance/provenance and acceptance evidence. Unknown original dates
stay Unknown; publication dates and Git commits use their actual dates.

The catalog describes practice implementations. “Accepted” requires an actual
matching platform receipt. No private chat transcript, full problem statement,
employer source, empty commit or backdated activity is part of this workflow.

---

<div align="center">
  <sub>Maintained by <a href="https://github.com/jyotirawattech">Jyoti Rawat</a> &bull; Systems & Platform Software Engineer &bull; Cisco</sub>
</div>
