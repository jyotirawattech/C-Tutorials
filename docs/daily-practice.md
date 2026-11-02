# Daily C practice workflow

Each useful entry contains a solution, an explanation and exercised tests. A daily
cadence is an intention, not a reason to create empty commits or claim unverified
problem acceptance.

## Prepare one entry

1. Choose one problem or revisit a concrete weakness in an existing solution.
   Search the catalog and folder names by problem number/title before adding it.
   Improve an existing entry for the same problem rather than duplicate it.
2. Add or update `solution.c` and its local `README.md`. Explain the approach,
   invariants, time and auxiliary-space complexity, ownership and cleanup.
3. Exercise normal inputs and relevant edge cases: empty/minimum input,
   boundaries, repeated values, no-match cases and allocation behavior where
   supported. Explain constraints the implementation assumes.
4. Run `make test`. Record the actual compiler/platform, solution assertions,
   sanitizer result, and any skipped leak detector separately.
5. Review the exact diff and provenance record, then publish only under the
   current approved GitHub workflow. One meaningful correction can be the day's
   work; missed days do not need catch-up or backdated commits.

Use [the entry template](practice-entry-template.md) for notes. Keep only the
fields relevant to the problem, but preserve evidence and date distinctions.

## Provenance and dates

- Mark a solution **Accepted** only when an actual platform receipt identifies
  the matching problem, submission and acceptance. A link, screenshot reference
  or receipt metadata may support the label; do not publish account tokens or
  private submission data.
- Otherwise describe the entry as **AI-assisted practice** or **local practice**
  according to the actual creation process, with **platform acceptance unverified**.
  Local tests prove the tested cases only. AI assistance is not an acceptance receipt.
- Keep the original practice date separate from the real publication date.
  The original date may be `Unknown`; do not infer it from an imported file or a
  reconstructed conversation. Set publication date only when publication occurs.
- Existing entries without recorded provenance remain `Unknown / needs review`;
  this workflow does not retroactively certify their authorship or acceptance.
- Write a short original problem summary and link to the public problem page.
  Do not copy full copyrighted problem statements, private Gemini conversations,
  employer code/logs, customer data, credentials or personal details.

## What the test runner establishes

The runner compiles each `solution.c` under strict C11 warnings with
UndefinedBehaviorSanitizer. UBSan findings stop execution through
`-fno-sanitize-recover=all`; a nonzero execution result fails the solution.
Use `SANITIZERS=address,undefined make test` to also enable AddressSanitizer on
a supported compiler/runtime. The default is `SANITIZERS=undefined`; an ASan
run must be recorded separately and is never implied by a default pass.

On systems with Apple's `leaks`, the runner also builds a plain binary for that
separate detector. Any nonzero detector exit is a failure, including a tooling
or permission failure. It is never converted into success by rerunning the binary.
An unavailable detector is explicitly skipped. `LEAK_CHECK=required make test`
requires that tool; `LEAK_CHECK=skip make test` explicitly skips only the separate
detector and still runs the sanitizer checks. Linux ASan also enables its integrated
leak detector. Platform/runtime support remains a prerequisite.

Passing assertions and enabled diagnostics is bounded validation, not a proof
of zero leaks or memory safety for every possible input. Some legacy solution
success messages say “zero leaks”; that text is not an independent detector result.

The CI configuration adds ASan on Linux and uses UBSan plus the separate leaks
tool on macOS for pushes and pull requests. It has read-only repository permission
and no scheduled commits, publishing credentials or automatic problem submissions.
Check the [actual workflow results](https://github.com/jyotirawattech/C-Tutorials/actions)
for the revision being reviewed; configuration alone does not establish a passing run.

Primary references: [Clang UBSan](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html)
and [Clang ASan](https://clang.llvm.org/docs/AddressSanitizer.html).
