#!/usr/bin/env bash
set -euo pipefail
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CASE_ROOT="$(mktemp -d "${TMPDIR:-/tmp}/c-tutorials-regression.XXXXXX")"
trap 'rm -rf -- "$CASE_ROOT"' EXIT
CASE_COUNT=0

prepare_case() {
    CASE_COUNT=$((CASE_COUNT + 1))
    CASE_DIR="$CASE_ROOT/case_$CASE_COUNT"
    mkdir -p "$CASE_DIR/scripts" "$CASE_DIR/sample with spaces"
    cp "$PROJECT_ROOT/scripts/run_tests.sh" "$CASE_DIR/scripts/run_tests.sh"
}
expect_result() {
    local expected="$1" pattern="$2"
    shift 2
    local status=0
    "$@" > "$CASE_DIR/result.log" 2>&1 || status=$?
    if [[ "$expected" == pass && "$status" != 0 ]] ||
       [[ "$expected" == fail && "$status" == 0 ]] ||
       ! grep -F "$pattern" "$CASE_DIR/result.log" >/dev/null; then
        cat "$CASE_DIR/result.log"
        printf 'FAIL: runner regression %d (exit %d)\n' "$CASE_COUNT" "$status" >&2
        exit 1
    fi
    printf 'PASS: runner regression %d (%s)\n' "$CASE_COUNT" "$pattern"
}

prepare_case
printf '%s\n' 'int main(void) { return 0; }' > "$CASE_DIR/sample with spaces/solution.c"
expect_result pass '0 passed, 1 skipped' env LEAK_CHECK=skip bash "$CASE_DIR/scripts/run_tests.sh"

prepare_case
printf '%s\n' 'int main(void) { return 0; }' > "$CASE_DIR/sample with spaces/solution.c"
mkdir "$CASE_DIR/mock"
printf '#!/usr/bin/env bash\nexit 23\n' > "$CASE_DIR/mock/leaks"
chmod +x "$CASE_DIR/mock/leaks"
expect_result fail 'FAIL: leaks returned nonzero' env LEAK_CHECK=auto PATH="$CASE_DIR/mock:$PATH" bash "$CASE_DIR/scripts/run_tests.sh"

prepare_case
printf '%s\n' 'int main(void) { return 7; }' > "$CASE_DIR/sample with spaces/solution.c"
expect_result fail 'FAIL: test or sanitizer execution' env LEAK_CHECK=skip bash "$CASE_DIR/scripts/run_tests.sh"

prepare_case
printf '%s\n' '#include <limits.h>' 'int main(void) { volatile int max = INT_MAX; volatile int one = 1; return (max + one) == 0; }' > "$CASE_DIR/sample with spaces/solution.c"
expect_result fail 'runtime error:' env LEAK_CHECK=skip bash "$CASE_DIR/scripts/run_tests.sh"

prepare_case
printf '%s\n' 'int main(void) { invalid_code; }' > "$CASE_DIR/sample with spaces/solution.c"
expect_result fail 'FAIL: compilation' env LEAK_CHECK=skip bash "$CASE_DIR/scripts/run_tests.sh"

prepare_case
expect_result fail 'FAIL: no solution.c files found' env LEAK_CHECK=skip bash "$CASE_DIR/scripts/run_tests.sh"

if [[ "${SANITIZERS:-undefined}" == address,undefined ]]; then
    prepare_case
    # Deliberately invalid, isolated fixture proves ASan findings fail the runner.
    printf '%s\n' '#include <stdlib.h>' 'int main(void) { char *p = malloc(1); if (!p) return 2; volatile int i = 1; p[i] = 1; free(p); return 0; }' > "$CASE_DIR/sample with spaces/solution.c"
    expect_result fail 'AddressSanitizer' env LEAK_CHECK=skip bash "$CASE_DIR/scripts/run_tests.sh"
else
    printf 'SKIP: ASan failure fixture (SANITIZERS=undefined)\n'
fi
printf 'Runner regressions: %d passed\n' "$CASE_COUNT"
