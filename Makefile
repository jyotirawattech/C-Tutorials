CC ?= clang

.PHONY: all test test-runner clean

all: test

test: test-runner
	@./scripts/run_tests.sh

test-runner:
	@bash ./scripts/test_runner.sh

clean:
	@find . -name "test_runner" -delete
	@find . -name "*.dSYM" -exec rm -rf {} + 2>/dev/null || true
	@echo "Cleaned build artifacts."
