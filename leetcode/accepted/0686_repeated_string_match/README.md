# 0686 — Repeated String Match

[Problem](https://leetcode.com/problems/repeated-string-match/) · [Accepted submission](https://leetcode.com/submissions/detail/2033715692/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 62 / 62 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 15, 2026 14:28**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Construct enough repeats of a to reach b's length and search that buffer for b. If there is no match, append one additional copy and search again; the extra copy covers a match beginning near a repetition boundary. Return the first sufficient repetition count or -1.

## Complexity

- Time: O(a+b) buffer construction, plus two substring searches; a conservative portable bound is O((a+b)*b) if substring search is naive, where a and b denote input lengths.
- Auxiliary space / ownership: O(a+b) allocated repeated buffer.

## Assumptions and review notes

Requires a nonempty source string and valid terminated inputs; empty a would divide by zero. Lengths/allocation arithmetic use int and rely on problem bounds. The checked allocation is freed on every completed path; memcpy sizes depend on those computed bounds, and the SIMD comment is not measured evidence.

- Nonempty divisor/string precondition
- memcpy buffer bounds depend on length arithmetic
- Unverified SIMD commentary

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
