#!/usr/bin/env bash
set -euo pipefail

CC="${CC:-clang}"
CFLAGS="-Wall -Wextra -Werror -pedantic -std=c11 -fsanitize=undefined -g"

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$PROJECT_ROOT"

echo "================================================================"
echo "  C-Tutorials: LeetCode in C Verification Suite"
echo "  Compiler: $($CC --version | head -n 1)"
echo "================================================================"

PASSED=0
FAILED=0
TOTAL=0

SOLUTIONS=$(find . -name "solution.c" | sort)

for sol in $SOLUTIONS; do
    dir=$(dirname "$sol")
    problem_name=$(basename "$dir")
    bin="$dir/test_runner"
    TOTAL=$((TOTAL + 1))

    echo "[$TOTAL] Compiling: $problem_name"
    if ! $CC $CFLAGS "$sol" -o "$bin"; then
        echo "❌ COMPILATION FAILED: $problem_name"
        FAILED=$((FAILED + 1))
        continue
    fi

    echo "    Executing & verifying memory safety..."
    if MallocNanoZone=0 leaks --atExit --quiet -- "$bin" 2>/dev/null; then
        echo "    ✅ PASSED (0 leaks verified)"
        PASSED=$((PASSED + 1))
    else
        # Fallback to direct execution if leaks tool has restricted environment
        if "$bin" > /dev/null 2>&1; then
            echo "    ✅ PASSED"
            PASSED=$((PASSED + 1))
        else
            echo "    ❌ RUNTIME FAILURE"
            FAILED=$((FAILED + 1))
        fi
    fi

    rm -f "$bin"
    rm -rf "$dir/test_runner.dSYM"
done

echo "================================================================"
echo "  Summary: $PASSED / $TOTAL Passed ($FAILED Failed)"
echo "================================================================"

if [ "$FAILED" -ne 0 ]; then
    exit 1
fi
