# Explain how much better, and why

Each solution note names a fair comparator and explains what changes in work,
memory, correctness or ownership. The result may be an advantage with conditions,
the same or worse performance, an unestablished improvement, or a known correctness
limitation. Use the conclusion supported by the code and evidence.

## Required comparison

1. **Baseline:** name the actual alternative, its input variables, time/space
   assumptions and expected result. Compare algorithms solving the same task.
   A named baseline is one stated alternative, not a claim that it is the best
   known algorithm or a representative of every other solution.
2. **Submitted approach:** describe its actual implementation and bounds. Include
   initialization, hashing collisions, recursion/output storage and bounded-key
   assumptions where relevant.
3. **How much:** show a defensible operation-count or growth model, or a measured
   result from a reproducible paired experiment. If no meaningful factor is
   established, state that explicitly.
4. **Why:** connect the difference to the avoided work or changed data structure.
5. **Trade-offs:** include extra storage, mutation/ownership, input constraints,
   worst-case behavior and correctness limitations that affect the conclusion.

For example, a brute-force stock-profit baseline considers n(n−1)/2 buy/sell
pairs. The archived prefix-minimum approach visits n−1 later days. At n=1000,
those counts are 499,500 candidate pairs and 999 scan iterations. These are different
algorithmic work units, **not a measured 500× runtime speedup**. Both approaches
can use O(1) auxiliary storage. The useful advantage is avoiding pair enumeration
while retaining the best earlier purchase price.

## Keep three evidence types separate

- **Algorithmic analysis:** derived from the named algorithms and assumptions.
  Big-O is a growth bound, not an exact stopwatch or byte count. Do not convert
  O(n²) versus O(n), by itself, into a measured speedup or percentage reduction.
- **LeetCode page snapshot:** reproduce the exact displayed runtime, memory and
  their separate `Beats` values, with the capture date and matching submission
  link. These are platform observations. A `Beats` percentile is not an elapsed
  time improvement percentage or a head-to-head comparison with our baseline.
  A display of 0 ms does not establish zero elapsed time or an infinite speedup.
- **Paired benchmark:** report a measured improvement only after testing the
  named baseline and candidate on equivalent inputs in the same environment.
  Record source revisions, compiler/options, machine, sizes/distributions,
  repetitions, timing method, variability and exactly which memory metric was
  measured. Publish the commands and result artifact. Otherwise mark it **not run**.

The current 83-entry archive records dated submission-page snapshots and static
comparisons. No new paired timing or memory benchmark is claimed. Precise `Beats`
cohort/tie/rounding semantics were not established from official Help Center
documentation, so the recorded label is preserved without inventing its formula.

## Correctness comes first

An incorrect implementation has no valid performance advantage over a correct
baseline. For historical problem 355, Design Twitter, retain the Accepted receipt and original
source while linking the [reproduced feed-order limitation](../leetcode/review/README.md).
Any corrected variant needs its own identity/tests; historical acceptance does
not automatically apply to the changed code.

## Publication check

Each accepted-source entry has a source-bound `comparison.json` and matching
comparison section. Run `make test-comparisons` to check required fields, source
identity, snapshot units/ranges/dates and the absence of invented measured gains.
Private capture matching is a separate local check. Schema checks do not prove
the mathematical analysis; review the comparator, bounds and work model too.

Preserve all original source hashes and solve/submission dates. A documentation
update has its actual update date; it does not create a new solve or a backdated
contribution. Keep the normal daily cadence and skip unchanged/no-work days.

## Official context

LeetCode documents its [language environments](https://support.leetcode.com/hc/en-us/articles/360011833974-What-are-the-environments-for-the-programming-languages),
the [Run/Submit workflow](https://support.leetcode.com/hc/en-us/articles/360012016874-Start-your-Coding-Practice)
and that [additional stdout can affect runtime](https://support.leetcode.com/hc/en-us/articles/360011834194-Am-I-allowed-to-print-something-to-stdout).
These references provide context; they do not establish a paired benchmark for
our archived code or a universal fastest/lowest-memory claim.
