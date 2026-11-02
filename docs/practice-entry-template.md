# <problem number and title>

Public problem URL: <canonical URL>
Original practice date: Unknown
Publication date: Unpublished
Provenance: Unknown / needs review
Platform acceptance: Unverified
Acceptance evidence: None recorded

## Original summary and constraints

Briefly restate the task in your own words. Link to the public statement instead
of copying it. State the input assumptions used by this implementation.

## Approach and reasoning

- Data structure and invariant:
- Why this approach:
- Alternative considered:
- Memory ownership and cleanup:

## Complexity

Time: <bound and the variables it uses>
Auxiliary space: <bound; distinguish output memory if relevant>

## How much better, and why?

Named baseline: <specific valid approach and the same problem constraints>

| Dimension | Baseline | This solution | Evidence and assumptions |
| --- | --- | --- | --- |
| Time | <bound> | <bound> | Theoretical analysis; state input variables and conditions |
| Auxiliary space | <bound> | <bound> | Distinguish working memory from output |
| Work at a stated input size | <count/model or Unknown> | <count/model or Unknown> | A theoretical work model is not timed speedup |

Why the difference: <mechanism/invariant that removes work or changes storage>
Trade-offs: <extra memory, constraints, constants, implementation complexity or correctness limits>
Verdict: Advantage with conditions / Same or worse / Not established / Known correctness limit

### Dated LeetCode UI snapshot, when actually captured

Source submission URL: <exact matching receipt URL or Not captured>
Captured at: <actual timestamp with timezone or Not captured>
Runtime display: <exact string> ms; runtime Beats: <exact percentage>
Memory display: <exact string> MB; memory Beats: <exact percentage>

These are the judge's displayed observations for that submission and capture date.
A Beats display is a separate platform comparison indicator, not that percent
faster or less memory than the named baseline. A displayed 0 ms is retained as a
UI value and is never used as a denominator or evidence of instant execution.
Missing judge data remains Not captured.

Paired local benchmark: Not run
Measured speedup factor: null
Measured memory reduction percent: null

For accepted archive entries, save the source-bound fields in comparison.json
and run make test-comparisons. The initial comparison gate permits no measured
gain fields; new paired benchmarks need their own reproducible evidence design.

## Edge cases exercised

| Case | Expected behavior | Actual local result |
| --- | --- | --- |
| Normal example | <expected> | Not run |
| Minimum/empty input if permitted | <expected> | Not run |
| Boundary or repeated values | <expected> | Not run |
| Failure/no-match path if relevant | <expected> | Not run |

## Validation receipt

Command: `make test`
Date/platform/compiler: Not run
Assertions and sanitizers: Not run
Separate leak detector: Not run / Skipped with reason / Passed / Failed
Known limitations: <unsupported cases or remaining tests>

## Reflection

What changed after testing, and what would you check next?
