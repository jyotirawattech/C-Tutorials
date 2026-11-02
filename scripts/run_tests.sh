#!/usr/bin/env bash
set -euo pipefail

# CC is one executable, never a shell command; flags remain an argument array.
CC="${CC:-clang}"
LEAK_CHECK="${LEAK_CHECK:-auto}"
SANITIZERS="${SANITIZERS:-undefined}"
case "$SANITIZERS" in
    undefined|address,undefined) ;;
    *) printf 'Invalid SANITIZERS: use undefined or address,undefined.\n' >&2; exit 2 ;;
esac
case "$LEAK_CHECK" in
    auto|required|skip) ;;
    *) printf 'Invalid LEAK_CHECK: use auto, required, or skip.\n' >&2; exit 2 ;;
esac
command -v "$CC" >/dev/null || { printf 'Compiler unavailable: %s\n' "$CC" >&2; exit 2; }

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$PROJECT_ROOT"
BUILD_DIR="$(mktemp -d "${TMPDIR:-/tmp}/c-tutorials-tests.XXXXXX")"
# Only the exact directory created above is removed; no repository glob cleanup.
trap 'rm -rf -- "$BUILD_DIR"' EXIT
CFLAGS=(-Wall -Wextra -Werror -pedantic -std=c11 -g -fno-omit-frame-pointer)
SANITIZER_FLAGS=("-fsanitize=$SANITIZERS" -fno-sanitize-recover=all)

LEAKS_AVAILABLE=false
if command -v leaks >/dev/null 2>&1; then LEAKS_AVAILABLE=true; fi
if [[ "$LEAK_CHECK" == required && "$LEAKS_AVAILABLE" == false ]]; then
    printf 'Required leaks tool is unavailable; no leak check was performed.\n' >&2
    exit 2
fi
ASAN_SETTINGS='halt_on_error=1:detect_leaks=0'
if [[ "$(uname -s)" == Linux ]]; then
    ASAN_SETTINGS='halt_on_error=1:detect_leaks=1'
fi

printf 'C-Tutorials: C11 tests with %s and fail-fast diagnostics\n' "$SANITIZERS"
"$CC" --version
PASSED=0
FAILED=0
TOTAL=0
LEAKS_PASSED=0
LEAKS_SKIPPED=0

# NUL-delimited discovery preserves paths containing spaces.
while IFS= read -r -d '' sol; do
    TOTAL=$((TOTAL + 1))
    problem_name="$(basename "$(dirname "$sol")")"
    bin="$BUILD_DIR/test_$TOTAL"
    printf '[%d] %s\n' "$TOTAL" "$problem_name"
    if ! "$CC" "${CFLAGS[@]}" "${SANITIZER_FLAGS[@]}" "$sol" -o "$bin"; then
        printf '    FAIL: compilation\n'
        FAILED=$((FAILED + 1))
        continue
    fi
    if ! ASAN_OPTIONS="$ASAN_SETTINGS" UBSAN_OPTIONS=halt_on_error=1 "$bin"; then
        printf '    FAIL: test or sanitizer execution\n'
        FAILED=$((FAILED + 1))
        continue
    fi
    if [[ "$LEAK_CHECK" != skip && "$LEAKS_AVAILABLE" == true ]]; then
        # Apple leaks runs a separate plain binary, not the ASan allocator.
        if ! "$CC" "${CFLAGS[@]}" "$sol" -o "$bin.plain"; then
            printf '    FAIL: leak-check binary compilation\n'
            FAILED=$((FAILED + 1))
            continue
        fi
        if ! MallocNanoZone=0 leaks --atExit --quiet -- "$bin.plain"; then
            # A detector/permission error is a failure too: never rerun to pass.
            printf '    FAIL: leaks returned nonzero (finding or tool failure)\n'
            FAILED=$((FAILED + 1))
            continue
        fi
        LEAKS_PASSED=$((LEAKS_PASSED + 1))
    else
        LEAKS_SKIPPED=$((LEAKS_SKIPPED + 1))
        if [[ "$LEAK_CHECK" == skip ]]; then
            printf '    SKIP: separate leaks check explicitly disabled\n'
        else
            printf '    SKIP: separate leaks tool unavailable\n'
        fi
    fi
    PASSED=$((PASSED + 1))
    printf '    PASS: exercised test assertions and enabled sanitizer checks\n'
done < <(find . -type f -name solution.c -not -path './.git/*' -print0)

printf 'Summary: %d / %d passed (%d failed)\n' "$PASSED" "$TOTAL" "$FAILED"
printf 'Separate leaks checks: %d passed, %d skipped\n' "$LEAKS_PASSED" "$LEAKS_SKIPPED"
if [[ "$TOTAL" == 0 ]]; then
    printf 'FAIL: no solution.c files found\n' >&2
    exit 1
fi
[[ "$FAILED" == 0 ]]
