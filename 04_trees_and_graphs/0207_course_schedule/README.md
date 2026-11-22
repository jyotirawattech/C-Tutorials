# 0207 · Course Schedule with checked graph storage

[Problem](https://leetcode.com/problems/course-schedule/) · [Archived submission and provenance](../../leetcode/accepted/0207_course_schedule/README.md)

This separately labelled C11 practice returns a distinct result for a feasible
schedule, a cycle, invalid input, and an allocation failure. Original practice
date for the historical submission: Unknown. This practice adaptation was
prepared with AI assistance on 22 November 2026. Its LeetCode verdict, runtime,
and memory results are **Not captured**. The original 2 November archive remains
unchanged.

## How it works

Each input pair lists a course and its prerequisite. Count each course's incoming
edges and pack outgoing edges into one target array. `offsets[u]` through
`offsets[u + 1]` identify the slice for prerequisite `u`. Reuse construction
cursors as the ready queue once the slices are filled.

Kahn's traversal removes one zero-indegree course at a time. The remaining
indegree is the number of incoming edges from courses still unprocessed. A course
enters the queue once, when its remaining count reaches zero. If the queue runs
out before every course is processed, the remaining graph contains a cycle.
Repeated edges contribute to the count and are removed separately. The caller
keeps ownership of the input. The function owns and releases all scratch buffers,
including after partial allocation failure.

The checked API takes a flat array of `CoursePrerequisite` pairs and `size_t`
counts. It accepts up to `INT_MAX` courses, checks endpoint ranges and size
arithmetic, and accepts an empty or edgeless graph without allocating. For a
nonempty pair list, the caller supplies storage for all declared pairs.

## How much changes

The named baseline is the [archived linked-edge-pool implementation](../../leetcode/accepted/0207_course_schedule/submission.c)
for the shared domain of valid inputs that fit its 2,000-course queue. Both
use Kahn traversal. For `V` courses and `E` edges, each takes O(V + E) time and
O(V + E) auxiliary storage, including the baseline's fixed queue. CSR builds
contiguous neighbor slices and traverses only real edges. The extra construction
passes and checked input path change constant work.

For 8-byte pointers and `size_t`, a 4-byte `int`, and 16-byte baseline edge nodes,
compare requested heap payload plus declared queue storage for E > 0. The baseline uses
`12V + 16E + 8,000` bytes. CSR uses `8(3V + 1) + 4E` bytes, counting its reused
queue buffer once.

| Same graph | Linked edge pool | Checked CSR | Difference |
| --- | ---: | ---: | ---: |
| V = 2,000, E = 5,000 | 112,000 B | 68,008 B | 43,992 B less |
| V = 2,000, E = 10 | 32,160 B | 48,048 B | 15,888 B more |

The saving on the first graph comes from removing per-edge pointers and padding.
On the sparse graph, the wider per-course arrays cost more. The checked API also
separates resource failure from cycles and sizes the queue to the input. The
model excludes input storage, allocator metadata and fixed local variables. It
estimates payload, rather than RSS, elapsed time or cache behavior. **Paired
benchmark: Not run.**

## Checks you can reproduce

Run `make test` from the repository root. On 22 November 2026, this harness
passed with strict C11 warnings and fail-fast UBSan. A reachability oracle
checked all 512 directed graphs on three vertices, including self-loops. The
allocation tracker injected 2,044 failures and checked that no scratch block
survived a failed return. Fixed cases exercised duplicates, invalid endpoints,
empty graphs and cycles. A nonempty 3,002-course graph started with 3,001 ready
courses and processed all 3,002, exercising queue storage beyond the original
fixed size. A separate local macOS `leaks` run passed for the harness. Local
ASan was not run.
