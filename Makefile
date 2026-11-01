CC ?= clang
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -fsanitize=undefined -g

.PHONY: all test clean

all: test

test:
	@./scripts/run_tests.sh

clean:
	@find . -name "test_runner" -delete
	@find . -name "*.dSYM" -exec rm -rf {} + 2>/dev/null || true
	@echo "Cleaned build artifacts."
