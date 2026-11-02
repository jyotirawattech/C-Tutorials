# Accepted LeetCode archive

[Jyoti Rawat's LeetCode profile](https://leetcode.com/u/user0592I/) · [Repository overview](../README.md)

**83 solved problems, 83 original accepted C sources**, checked against the signed-in problem history on 2 November 2026. Each entry links its problem and matching accepted submission, preserves the rendered source, and records the original displayed date separately from this archive date. One attempted-only problem has no accepted source and is outside this solved set.

The twelve standalone practice examples elsewhere in this repository are a separate, partly overlapping collection. They are not twelve additional accepted solves. This archive selects one accepted C submission per solved problem, rather than duplicating every language variant or attempt.

## What can be reproduced

```sh
make test             # twelve standalone algorithm harnesses and integrity regressions
make test-accepted    # all 83 source hashes/metadata and isolated C object compilation
```

The archive compilation uses standard headers plus explicit judge-provided list/tree types from `scripts/leetcode_compat.h`. Source files are compiled independently; the accepted implementations are not rewritten. Compilation does not rerun LeetCode's tests or prove runtime correctness for every input. See the [source-review boundaries and confirmed finding](review/README.md).

Historical platform acceptance is preserved even where later review identifies a limitation. No source is described as universally memory-safe or leak-free. Original assistance and practice dates remain Unknown where not evidenced. The archive/notes are AI-assisted; original source comments are preserved as historical content, not endorsed measurements.

## Catalog

| ID | Problem and explanation | Source receipt | Displayed submission date |
| --- | --- | --- | --- |
| 1 | [Two Sum](accepted/0001_two_sum/README.md) | [Accepted](https://leetcode.com/submissions/detail/2037075478/) | Jun 18, 2026 |
| 22 | [Generate Parentheses](accepted/0022_generate_parentheses/README.md) | [Accepted](https://leetcode.com/submissions/detail/2046778526/) | Jun 26, 2026 |
| 26 | [Remove Duplicates from Sorted Array](accepted/0026_remove_duplicates_from_sorted_array/README.md) | [Accepted](https://leetcode.com/submissions/detail/2035054515/) | Jun 16, 2026 |
| 27 | [Remove Element](accepted/0027_remove_element/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033798016/) | Jun 15, 2026 |
| 33 | [Search in Rotated Sorted Array](accepted/0033_search_in_rotated_sorted_array/README.md) | [Accepted](https://leetcode.com/submissions/detail/2040565062/) | Jun 21, 2026 |
| 41 | [First Missing Positive](accepted/0041_first_missing_positive/README.md) | [Accepted](https://leetcode.com/submissions/detail/2037084114/) | Jun 18, 2026 |
| 56 | [Merge Intervals](accepted/0056_merge_intervals/README.md) | [Accepted](https://leetcode.com/submissions/detail/2046774188/) | Jun 26, 2026 |
| 80 | [Remove Duplicates from Sorted Array II](accepted/0080_remove_duplicates_from_sorted_array_ii/README.md) | [Accepted](https://leetcode.com/submissions/detail/2035107421/) | Jun 16, 2026 |
| 83 | [Remove Duplicates from Sorted List](accepted/0083_remove_duplicates_from_sorted_list/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033723539/) | Jun 15, 2026 |
| 84 | [Largest Rectangle in Histogram](accepted/0084_largest_rectangle_in_histogram/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033033041/) | Jun 14, 2026 |
| 88 | [Merge Sorted Array](accepted/0088_merge_sorted_array/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033796939/) | Jun 15, 2026 |
| 106 | [Construct Binary Tree from Inorder and Postorder Traversal](accepted/0106_construct_binary_tree_from_inorder_and_postorder_traversal/README.md) | [Accepted](https://leetcode.com/submissions/detail/2041565369/) | Jun 22, 2026 |
| 121 | [Best Time to Buy and Sell Stock](accepted/0121_best_time_to_buy_and_sell_stock/README.md) | [Accepted](https://leetcode.com/submissions/detail/2046785680/) | Jun 26, 2026 |
| 122 | [Best Time to Buy and Sell Stock II](accepted/0122_best_time_to_buy_and_sell_stock_ii/README.md) | [Accepted](https://leetcode.com/submissions/detail/450652093/) | Feb 01, 2021 |
| 138 | [Copy List with Random Pointer](accepted/0138_copy_list_with_random_pointer/README.md) | [Accepted](https://leetcode.com/submissions/detail/2037081804/) | Jun 18, 2026 |
| 141 | [Linked List Cycle](accepted/0141_linked_list_cycle/README.md) | [Accepted](https://leetcode.com/submissions/detail/2043139098/) | Jun 23, 2026 |
| 146 | [LRU Cache](accepted/0146_lru_cache/README.md) | [Accepted](https://leetcode.com/submissions/detail/2046774028/) | Jun 26, 2026 |
| 147 | [Insertion Sort List](accepted/0147_insertion_sort_list/README.md) | [Accepted](https://leetcode.com/submissions/detail/2040538204/) | Jun 21, 2026 |
| 150 | [Evaluate Reverse Polish Notation](accepted/0150_evaluate_reverse_polish_notation/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033021128/) | Jun 14, 2026 |
| 189 | [Rotate Array](accepted/0189_rotate_array/README.md) | [Accepted](https://leetcode.com/submissions/detail/463974219/) | Mar 06, 2021 |
| 198 | [House Robber](accepted/0198_house_robber/README.md) | [Accepted](https://leetcode.com/submissions/detail/2046775170/) | Jun 26, 2026 |
| 200 | [Number of Islands](accepted/0200_number_of_islands/README.md) | [Accepted](https://leetcode.com/submissions/detail/2046776629/) | Jun 26, 2026 |
| 206 | [Reverse Linked List](accepted/0206_reverse_linked_list/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033793518/) | Jun 15, 2026 |
| 207 | [Course Schedule](accepted/0207_course_schedule/README.md) | [Accepted](https://leetcode.com/submissions/detail/2049492075/) | Jun 29, 2026 |
| 215 | [Kth Largest Element in an Array](accepted/0215_kth_largest_element_in_an_array/README.md) | [Accepted](https://leetcode.com/submissions/detail/2040535241/) | Jun 21, 2026 |
| 217 | [Contains Duplicate](accepted/0217_contains_duplicate/README.md) | [Accepted](https://leetcode.com/submissions/detail/463988887/) | Mar 06, 2021 |
| 232 | [Implement Queue using Stacks](accepted/0232_implement_queue_using_stacks/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033038568/) | Jun 14, 2026 |
| 328 | [Odd Even Linked List](accepted/0328_odd_even_linked_list/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033789935/) | Jun 15, 2026 |
| 352 | [Data Stream as Disjoint Intervals](accepted/0352_data_stream_as_disjoint_intervals/README.md) | [Accepted](https://leetcode.com/submissions/detail/2029363865/) | Jun 11, 2026 |
| 355 | [Design Twitter](accepted/0355_design_twitter/README.md) | [Accepted](https://leetcode.com/submissions/detail/2029610348/) | Jun 11, 2026 |
| 373 | [Find K Pairs with Smallest Sums](accepted/0373_find_k_pairs_with_smallest_sums/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033580722/) | Jun 15, 2026 |
| 380 | [Insert Delete GetRandom O(1)](accepted/0380_insert_delete_getrandom_o1/README.md) | [Accepted](https://leetcode.com/submissions/detail/2029370742/) | Jun 11, 2026 |
| 381 | [Insert Delete GetRandom O(1) - Duplicates allowed](accepted/0381_insert_delete_getrandom_o1_duplicates_allowed/README.md) | [Accepted](https://leetcode.com/submissions/detail/2029527256/) | Jun 11, 2026 |
| 432 | [All O\`one Data Structure](accepted/0432_all_oone_data_structure/README.md) | [Accepted](https://leetcode.com/submissions/detail/2029540776/) | Jun 11, 2026 |
| 448 | [Find All Numbers Disappeared in an Array](accepted/0448_find_all_numbers_disappeared_in_an_array/README.md) | [Accepted](https://leetcode.com/submissions/detail/2032943655/) | Jun 14, 2026 |
| 459 | [Repeated Substring Pattern](accepted/0459_repeated_substring_pattern/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033708350/) | Jun 15, 2026 |
| 460 | [LFU Cache](accepted/0460_lfu_cache/README.md) | [Accepted](https://leetcode.com/submissions/detail/2029340112/) | Jun 11, 2026 |
| 482 | [License Key Formatting](accepted/0482_license_key_formatting/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033701198/) | Jun 15, 2026 |
| 485 | [Max Consecutive Ones](accepted/0485_max_consecutive_ones/README.md) | [Accepted](https://leetcode.com/submissions/detail/2032923073/) | Jun 14, 2026 |
| 493 | [Reverse Pairs](accepted/0493_reverse_pairs/README.md) | [Accepted](https://leetcode.com/submissions/detail/2041566308/) | Jun 22, 2026 |
| 520 | [Detect Capital](accepted/0520_detect_capital/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033696432/) | Jun 15, 2026 |
| 633 | [Sum of Square Numbers](accepted/0633_sum_of_square_numbers/README.md) | [Accepted](https://leetcode.com/submissions/detail/2040541036/) | Jun 21, 2026 |
| 636 | [Exclusive Time of Functions](accepted/0636_exclusive_time_of_functions/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033025116/) | Jun 14, 2026 |
| 645 | [Set Mismatch](accepted/0645_set_mismatch/README.md) | [Accepted](https://leetcode.com/submissions/detail/2032936506/) | Jun 14, 2026 |
| 686 | [Repeated String Match](accepted/0686_repeated_string_match/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033715692/) | Jun 15, 2026 |
| 703 | [Kth Largest Element in a Stream](accepted/0703_kth_largest_element_in_a_stream/README.md) | [Accepted](https://leetcode.com/submissions/detail/2029347190/) | Jun 11, 2026 |
| 704 | [Binary Search](accepted/0704_binary_search/README.md) | [Accepted](https://leetcode.com/submissions/detail/2040540292/) | Jun 21, 2026 |
| 715 | [Range Module](accepted/0715_range_module/README.md) | [Accepted](https://leetcode.com/submissions/detail/2029644041/) | Jun 11, 2026 |
| 739 | [Daily Temperatures](accepted/0739_daily_temperatures/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033029335/) | Jun 14, 2026 |
| 796 | [Rotate String](accepted/0796_rotate_string/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033710099/) | Jun 15, 2026 |
| 831 | [Masking Personal Information](accepted/0831_masking_personal_information/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033706140/) | Jun 15, 2026 |
| 852 | [Peak Index in a Mountain Array](accepted/0852_peak_index_in_a_mountain_array/README.md) | [Accepted](https://leetcode.com/submissions/detail/2040539355/) | Jun 21, 2026 |
| 912 | [Sort an Array](accepted/0912_sort_an_array/README.md) | [Accepted](https://leetcode.com/submissions/detail/2040536510/) | Jun 21, 2026 |
| 932 | [Beautiful Array](accepted/0932_beautiful_array/README.md) | [Accepted](https://leetcode.com/submissions/detail/2041563723/) | Jun 22, 2026 |
| 994 | [Rotting Oranges](accepted/0994_rotting_oranges/README.md) | [Accepted](https://leetcode.com/submissions/detail/2046777765/) | Jun 26, 2026 |
| 1032 | [Stream of Characters](accepted/1032_stream_of_characters/README.md) | [Accepted](https://leetcode.com/submissions/detail/2029357663/) | Jun 11, 2026 |
| 1046 | [Last Stone Weight](accepted/1046_last_stone_weight/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033567278/) | Jun 15, 2026 |
| 1071 | [Greatest Common Divisor of Strings](accepted/1071_greatest_common_divisor_of_strings/README.md) | [Accepted](https://leetcode.com/submissions/detail/2041863308/) | Jun 22, 2026 |
| 1200 | [Minimum Absolute Difference](accepted/1200_minimum_absolute_difference/README.md) | [Accepted](https://leetcode.com/submissions/detail/2040527387/) | Jun 21, 2026 |
| 1354 | [Construct Target Array With Multiple Sums](accepted/1354_construct_target_array_with_multiple_sums/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033686478/) | Jun 15, 2026 |
| 1365 | [How Many Numbers Are Smaller Than the Current Number](accepted/1365_how_many_numbers_are_smaller_than_the_current_number/README.md) | [Accepted](https://leetcode.com/submissions/detail/2032937879/) | Jun 14, 2026 |
| 1441 | [Build an Array With Stack Operations](accepted/1441_build_an_array_with_stack_operations/README.md) | [Accepted](https://leetcode.com/submissions/detail/2032945463/) | Jun 14, 2026 |
| 1470 | [Shuffle the Array](accepted/1470_shuffle_the_array/README.md) | [Accepted](https://leetcode.com/submissions/detail/2032914942/) | Jun 14, 2026 |
| 1475 | [Final Prices With a Special Discount in a Shop](accepted/1475_final_prices_with_a_special_discount_in_a_shop/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033027189/) | Jun 14, 2026 |
| 1476 | [Subrectangle Queries](accepted/1476_subrectangle_queries/README.md) | [Accepted](https://leetcode.com/submissions/detail/2029644148/) | Jun 11, 2026 |
| 1578 | [Minimum Time to Make Rope Colorful](accepted/1578_minimum_time_to_make_rope_colorful/README.md) | [Accepted](https://leetcode.com/submissions/detail/462403664/) | Mar 02, 2021 |
| 1590 | [Make Sum Divisible by P](accepted/1590_make_sum_divisible_by_p/README.md) | [Accepted](https://leetcode.com/submissions/detail/2040516582/) | Jun 21, 2026 |
| 1664 | [Ways to Make a Fair Array](accepted/1664_ways_to_make_a_fair_array/README.md) | [Accepted](https://leetcode.com/submissions/detail/2040524225/) | Jun 21, 2026 |
| 1700 | [Number of Students Unable to Eat Lunch](accepted/1700_number_of_students_unable_to_eat_lunch/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033035894/) | Jun 14, 2026 |
| 1732 | [Find the Highest Altitude](accepted/1732_find_the_highest_altitude/README.md) | [Accepted](https://leetcode.com/submissions/detail/2037096592/) | Jun 18, 2026 |
| 1768 | [Merge Strings Alternately](accepted/1768_merge_strings_alternately/README.md) | [Accepted](https://leetcode.com/submissions/detail/2041859979/) | Jun 22, 2026 |
| 1887 | [Reduction Operations to Make the Array Elements Equal](accepted/1887_reduction_operations_to_make_the_array_elements_equal/README.md) | [Accepted](https://leetcode.com/submissions/detail/2040528794/) | Jun 21, 2026 |
| 1929 | [Concatenation of Array](accepted/1929_concatenation_of_array/README.md) | [Accepted](https://leetcode.com/submissions/detail/2031672202/) | Jun 13, 2026 |
| 1944 | [Number of Visible People in a Queue](accepted/1944_number_of_visible_people_in_a_queue/README.md) | [Accepted](https://leetcode.com/submissions/detail/2049493001/) | Jun 29, 2026 |
| 1967 | [Number of Strings That Appear as Substrings in Word](accepted/1967_number_of_strings_that_appear_as_substrings_in_word/README.md) | [Accepted](https://leetcode.com/submissions/detail/2049518696/) | Jun 29, 2026 |
| 2043 | [Simple Bank System](accepted/2043_simple_bank_system/README.md) | [Accepted](https://leetcode.com/submissions/detail/2029605836/) | Jun 11, 2026 |
| 2073 | [Time Needed to Buy Tickets](accepted/2073_time_needed_to_buy_tickets/README.md) | [Accepted](https://leetcode.com/submissions/detail/2033036947/) | Jun 14, 2026 |
| 2080 | [Range Frequency Queries](accepted/2080_range_frequency_queries/README.md) | [Accepted](https://leetcode.com/submissions/detail/2029635919/) | Jun 11, 2026 |
| 2144 | [Minimum Cost of Buying Candies With Discount](accepted/2144_minimum_cost_of_buying_candies_with_discount/README.md) | [Accepted](https://leetcode.com/submissions/detail/2046771410/) | Jun 26, 2026 |
| 3532 | [Path Existence Queries in a Graph I](accepted/3532_path_existence_queries_in_a_graph_i/README.md) | [Accepted](https://leetcode.com/submissions/detail/2061378248/) | Jul 09, 2026 |
| 3739 | [Count Subarrays With Majority Element II](accepted/3739_count_subarrays_with_majority_element_ii/README.md) | [Accepted](https://leetcode.com/submissions/detail/2046769368/) | Jun 26, 2026 |
| 3754 | [Concatenate Non-Zero Digits and Multiply by Sum I](accepted/3754_concatenate_non_zero_digits_and_multiply_by_sum_i/README.md) | [Accepted](https://leetcode.com/submissions/detail/2058859407/) | Jul 07, 2026 |
| 3756 | [Concatenate Non-Zero Digits and Multiply by Sum II](accepted/3756_concatenate_non_zero_digits_and_multiply_by_sum_ii/README.md) | [Accepted](https://leetcode.com/submissions/detail/2060383645/) | Jul 08, 2026 |
