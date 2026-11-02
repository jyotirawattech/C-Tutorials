# 2073 — Time Needed to Buy Tickets

[Problem](https://leetcode.com/problems/time-needed-to-buy-tickets/) · [Accepted submission](https://leetcode.com/submissions/detail/2033036947/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 65 / 65 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 14, 2026 22:18**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Count how many turns each person can take before the target person buys their final ticket. People at or before the target can receive at most target tickets, while later people can receive at most target-1. Summing these capped contributions avoids simulating repeated queue rotations.

## Complexity

- Time: O(n), where n=ticketsSize
- Auxiliary space / ownership: O(1) auxiliary space

## Assumptions and review notes

The target index must be valid and its ticket count positive. The source assumes bounded positive ticket counts so the accumulated total fits int; it does not validate arbitrary inputs.

- No allocation or dangerous library call observed.
- Source comment claims 'blistering fast ALU bounds checking'; static inspection establishes capped counting, not a speed measurement.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
