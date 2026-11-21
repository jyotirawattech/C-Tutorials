# Beautiful Array: checked allocation practice

[Public problem](https://leetcode.com/problems/beautiful-array/) ·
[Unchanged historical source](../../leetcode/accepted/0932_beautiful_array/submission.c)

This C11 adaptation keeps the iterative odd/even construction and its two
buffers. The change is a checked failure contract and cleanup after a partial
allocation failure. It is not a normal-input judge counterexample or a new solve.

## Contract and ownership

```c
BeautifulArrayStatus beautiful_array_checked(int n, int **out_values, int *out_size);
```

This practice deliberately supports `1 <= n <= 1000`. That cap bounds the
arithmetic and the test domain; it is not a promise about larger positive `int`
values. Output slots must be valid, writable, separate storage for a fresh
result. Release a previously owned result before reusing those slots.

- `BEAUTIFUL_ARRAY_OK`: returns an owned `malloc` array through `out_values`,
  sets `out_size` to `n`, and has already freed the scratch buffer. The caller
  frees the returned array once.
- `BEAUTIFUL_ARRAY_INVALID_ARGUMENT`: an output argument is NULL or the size is
  outside the supported range or allocation-size arithmetic. Each non-NULL
  output slot is reset to NULL or zero; NULL slots are not dereferenced.
- `BEAUTIFUL_ARRAY_NO_MEMORY`: allocation failed, output pointer/size are
  NULL/zero, and this call retains no allocated block.

The first allocation is checked before requesting the second. If the second
fails, the first is released. A private helper accepts allocation/release
callbacks for deterministic tests; the public wrapper always uses `malloc`
and `free`. This example does not preserve an old allocation passed through
an output slot or support aliasing output slots with one another.

## Construction and invariant

Start with `[1]`. Each pass emits legal odd images of the current order, then
legal even images, into the temporary buffer and copies that order back. If the
current order covers `1..count`, the next covers `1..min(2*count,n)` exactly once.
Each mapping preserves the absence of a midpoint within its half. An endpoint
from each half has odd sum, so it cannot equal twice an integer middle value.
Filtering values above `n` does not introduce a forbidden subsequence.

The bounded size makes the doubled intermediate values safe. The size check
also precedes multiplying by `sizeof(int)`. No larger-input overflow claim is
made for either the adaptation or the historical implementation.

## How much better, and why?

**Named baseline:** the unchanged archived two-buffer iterative constructor,
restricted to the same `1..1000` comparison domain. Both implementations have
O(n) time: pass lengths grow geometrically. Both use O(n) temporary storage
plus O(n) returned storage, two allocations on success, and peak requested
array payload `2*n*sizeof(int)`. Normal-path storage and dominant time bounds
are unchanged. No speedup is established.

The actual difference is at failed returns. The historical function requests
both arrays before testing either pointer. When only one allocation fails, it
returns NULL without releasing the other and leaves its reported size at `n`.
The test-only include executes that unchanged function at `n=8`, failing
allocation one and allocation two separately. Each return retains **one
`8*sizeof(int)` requested block**. The checked helper retains **zero blocks**
and reports NULL/zero in both injected cases. On the recorded ABI,
`sizeof(int)=4`, so the retained requested payload is 32 bytes versus zero.
For the first failure, the checked path also avoids the second allocation
attempt. These are precise fixture/resource observations, not RSS measurements,
an end-to-end memory percentage or a timing benchmark.

The trade-offs are a new status/output API, explicit ownership requirements and
a deliberately bounded input domain. Successful construction still reserves
both arrays. Allocation-failure correctness is the benefit; normal performance
improvement is not claimed.

Paired timing/memory benchmark: **Not run**. Measured speedup factor: **null**.
Measured memory reduction percent: **null**.

## Bounded tests and baseline execution

The public wrapper constructs one output for every supported size `1..1000`.
The independent oracle first checks a permutation of `1..n`, records each value's
position, then checks every same-parity endpoint pair. Its midpoint must not lie
between those endpoint positions. This O(n²) test oracle does not repeat the
constructor's odd/even control flow; its cost is separate from O(n) construction.

The harness also runs:

- 2,000 injected failures: both allocation positions for every supported size,
  checking status, cleared outputs, allocation attempts and cleanup.
- 18 invalid-argument calls: eight size/NULL-output cases through both default
  and tracked paths, plus two invalid callback cases for the private seam.
- One tracked checked-success control, confirming two allocations, one returned
  block and the stated peak requested payload before caller cleanup.
- Two historical failure cases and one historical successful control at `n=8`.
  Allocation/function-name macros apply only around the unchanged source include
  and are immediately undefined. The test registry records the retained block
  at the old failed return, then explicitly reclaims it. The test itself does
  not intentionally leave that allocation live at process exit.

The archived source lacks a final newline. A Clang diagnostic push/ignore/pop
suppresses only `-Wnewline-eof` around that include; new code retains strict
warnings. Its bytes and historical metadata are unchanged. The metadata's
2 November static-only observation is dated history: **this separate 21 November
harness executes only the stated controlled original-932 cases**. The archive-wide
`make test-accepted` target still performs object compilation, not execution of
all 83 archived algorithms.

Assertions are required; `NDEBUG` builds are rejected. All tracked fixtures are
cleaned up, but finite assertions and sanitizer results are not a universal
correctness, leak-free or memory-safety guarantee.

## Provenance and validation

Adaptation/test/documentation work: **21 November 2026**, AI-assisted. Original
practice date and original assistance: **Unknown**. Exact platform acceptance,
runtime, memory and Beats values for this checked API: **Not captured**.

The [historical receipt](../../leetcode/accepted/0932_beautiful_array/metadata.json)
records C, Accepted **38 / 38**, [submission 2041563723](https://leetcode.com/submissions/detail/2041563723/),
displayed **Jun 22, 2026 09:19**, timezone unspecified, captured on
**2026-11-02T13:49:25.262Z**. Those observations apply to the unchanged original
source, not this adaptation. Its original source SHA-256 remains
`39682d391631f05c31207643db2affe623ec5ec2af91f6aa71ba79e0a3e5b288`.

From this directory:

```bash
clang -Wall -Wextra -Werror -pedantic -std=c11 -g -fno-omit-frame-pointer \
  -fsanitize=undefined -fno-sanitize-recover=all solution.c -o /tmp/beautiful-array-check
UBSAN_OPTIONS=halt_on_error=1 /tmp/beautiful-array-check
```

Actual targeted validation on **21 November 2026** passed strict C11 compilation
and fail-fast UBSan on macOS with Apple clang 17.0.0 (clang-1700.0.13.5):

```text
[PASSED] Beautiful Array checked practice: 1000 property cases, 2000 allocation failures, 18 invalid arguments, 1 checked allocation control, 2 historical failure cases, 1 historical success control; zero tracked blocks after fixture cleanup.
```

The repository's `make test` command also discovers this harness. Public Linux
ASan/UBSan and macOS UBSan job outcomes must be read back for the actual revision;
configured jobs are not evidence of a completed run. Local ASan was not run
because of the documented host runtime stall. This targeted worker check does
not invoke a separate leak detector.
