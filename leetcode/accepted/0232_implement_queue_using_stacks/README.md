# 0232 — Implement Queue using Stacks

[Problem](https://leetcode.com/problems/implement-queue-using-stacks/) · [Accepted submission](https://leetcode.com/submissions/detail/2033038568/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 23 / 23 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 14, 2026 22:20**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Push new elements onto an input stack and remove elements from an output stack. Transfer the entire input stack only when the output stack is empty, reversing the order so the oldest queued value is next. Each element moves between stacks at most once before removal.

## Complexity

- Time: Push and empty are O(1); pop and peek are amortized O(1), with O(k) for an individual transfer of k queued elements.
- Auxiliary space / ownership: Two fixed arrays of 100 integers, O(1) for the implemented capacity; a scalable form would use O(q) for queue capacity q.

## Assumptions and review notes

The submitted implementation assumes the platform's operation/capacity bounds and valid nonempty pop/peek calls. It does not grow the fixed arrays or handle allocation failure; repeated pushes beyond the allowed capacity would write out of bounds.

- Fixed-capacity stacks without overflow checks
- Empty pop/peek unchecked
- Unchecked malloc result

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
