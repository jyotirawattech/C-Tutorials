# 1032 — Stream of Characters

[Problem](https://leetcode.com/problems/stream-of-characters/) · [Accepted submission](https://leetcode.com/submissions/detail/2029357663/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 20 / 20 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 11, 2026 11:36**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Insert dictionary words backward into a trie. Each incoming character extends the stream, and a query walks backward through recent characters up to the longest dictionary word; reaching a word-marked trie node proves a matching suffix. A missing edge stops the search immediately.

## Complexity

- Time: Create O(P+S), for preallocated trie size P=400005 and total dictionary characters S; each query O(L), where L is the longest word length.
- Auxiliary space / ownership: O(P+Q), for the fixed trie allocation and stream buffer Q=40005; no storage is reclaimed as the stream grows.

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Compare every dictionary word with the stream suffix. For each query, test each word's characters against the current stream ending.

- Baseline time: O(S) worst case per query, S total dictionary characters. Space: Dictionary and recent stream storage.
- Submitted approach: Reversed-word trie. Time: O(P+S) build; O(L) per query, L longest word. Space: Fixed P=400005 trie nodes and Q=40005 stream characters.

**How much, by analysis:** A query follows at most L trie edges rather than comparing up to S dictionary characters in the stated baseline. Build cost and the preallocated P-node memory must be included; no measured speedup or exact query savings are known.

**Why:** Shared reversed prefixes let one backward stream walk test many dictionary suffixes together.

**Trade-offs and conditions:** Only lowercase a..z and bounded total nodes/queries are supported. Fixed allocation can be wasteful for small dictionaries, and capacity/allocation failures are unchecked.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2029357663/) displayed the following at capture on **2026-11-02T13:45:42.782Z**:

- Runtime: **47 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **141.70 MB**; reported memory `Beats`: **92.86%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

Requires lowercase a..z characters and dictionary/query totals fitting the fixed trie and stream capacities. Neither capacity nor allocation failures are checked. strlen assumes valid terminated dictionary strings; test suffix matches, overlapping words and a stream longer than the longest word.

- Fixed trie and stream capacities
- Unchecked malloc/calloc results
- Alphabet-index and string-termination preconditions

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
