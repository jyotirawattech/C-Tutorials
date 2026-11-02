# 0636 — Exclusive Time of Functions

[Problem](https://leetcode.com/problems/exclusive-time-of-functions/) · [Accepted submission](https://leetcode.com/submissions/detail/2033025116/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 120 / 120 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 14, 2026 22:07**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Maintain a stack of currently active function IDs and a timestamp for the next unaccounted execution interval. A start event credits the previous active function before pushing the new one; an end event credits through its inclusive timestamp, pops it, and advances the timestamp by one. The stack models nested calls while the result array accumulates exclusive time.

## Complexity

- Time: O(n + L), where n is the number of function IDs and L is the total length of all log strings.
- Auxiliary space / ownership: O(m) auxiliary call stack for m logs, plus O(n) result storage.

## Assumptions and review notes

Requires well-formed, correctly nested logs with valid function IDs and timestamps in int range. The hand-written parser does not validate separators or stack balance; malformed logs can overrun strings or the stack. The caller must free the result array.

- Unchecked calloc/malloc results
- Unbounded parsing depends on valid log format
- Integer timestamp accumulation depends on problem bounds

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
