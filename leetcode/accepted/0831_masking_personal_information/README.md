# 0831 — Masking Personal Information

[Problem](https://leetcode.com/problems/masking-personal-information/) · [Accepted submission](https://leetcode.com/submissions/detail/2033706140/) · [LeetCode profile](https://leetcode.com/u/user0592I/)

## Provenance

- Observed platform result: **Accepted**, 66 / 66 test cases, C, on Jyoti Rawat's `user0592I` profile.
- Displayed submission time: **Jun 15, 2026 14:19**; timezone unspecified on the page.
- GitHub archive date: **2 November 2026**. Original practice date and original assistance are Unknown; this is not a new solve-date claim.
- `submission.c` preserves the source text rendered by the selected submission page, omitting display line numbers. Its SHA-256 is recorded in [metadata.json](metadata.json). Explanations and archive tooling were prepared with AI assistance.

## Approach and invariant

Scan once to distinguish an email from a phone string and retain either the at-sign position or the final four digits. For email input, lowercase the retained boundary characters and domain while replacing the middle of the local name. For phone input, select a country-code mask by digit count and append the masked local prefix and saved final digits.

## Complexity

- Time: O(n), where n is input length
- Auxiliary space / ownership: O(1) auxiliary scan state plus O(n) returned storage for email (bounded mask storage for a phone)

## How this solution compares

**Conclusion:** Advantage with conditions.

**Named baseline:** Build normalized intermediate email/phone buffers. Copy/lowercase the full email or collect all phone digits before constructing the mask.

- Baseline time: O(n). Space: O(n) intermediate storage plus the output.
- Submitted approach: Single scan with a four-digit rolling phone buffer. Time: O(n), where n is input length. Space: O(1) auxiliary scan state plus O(n) returned storage for email (bounded mask storage for a phone).

**How much, by analysis:** For a d-digit phone, the archive retains four digit characters instead of a d-character normalized digit buffer. Both still scan the input and construct the mask in linear work; with the bounded 10..13-digit phone contract this is a small storage trade-off, not a benchmarked speed gain.

**Why:** The archive retains only the phone suffix needed by the output, and reads email characters directly when producing its result.

**Trade-offs and conditions:** Rolling the four digits performs several assignments per digit. Valid ASCII email/phone formats and unchecked allocations remain assumptions; masking is not a general anonymization guarantee.

### Submission-page performance snapshot

The matching [submission page](https://leetcode.com/submissions/detail/2033706140/) displayed the following at capture on **2026-11-02T13:52:25.823Z**:

- Runtime: **0 ms**; reported runtime `Beats`: **100.00%**.
- Memory: **8.62 MB**; reported memory `Beats`: **18.31%**.

These are dated platform observations, not a measured improvement over the named baseline. A `Beats` value is not a percentage speedup; a 0 ms display does not establish zero elapsed time. **Paired timing/memory benchmark: not run.** No measured speedup factor or memory reduction is claimed. See the [comparison standard](../../../docs/comparison-guidance.md) and [source-bound comparison data](comparison.json).

## Assumptions and review notes

The code assumes the problem's valid ASCII email format or a phone containing 10..13 digits. Other phone digit counts index outside the country-prefix array, and result allocations are unchecked; this formatting exercise is not a general anonymization/privacy guarantee.

- Unchecked result allocations.
- country[digit_count-10] assumes a validated 10..13-digit phone contract.
- ASCII-only uppercase conversion by +32 and valid at-sign/local-name positions are assumed.
- Uses strlen on fixed prefix literals, flagged by selected safe-C guidance; original code preserved.

## Validation scope

`python3 scripts/check_accepted.py --compile` from the repository root checks source hashes, links, owner/verdict metadata, coverage and isolated object compilation with the documented LeetCode environment declarations. It does **not** execute every archived algorithm. The twelve standalone practice harnesses have a separate `make test` run. Platform acceptance, local compilation, static review and behavioral tests are distinct observations; source comments are not independent benchmarks or universal safety guarantees.
