CC ?= clang

.PHONY: all test test-runner test-archive-integrity test-accepted clean

all: test

test: test-runner test-archive-integrity
	@./scripts/run_tests.sh

test-runner:
	@bash ./scripts/test_runner.sh

test-archive-integrity:
	@PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests -v

test-accepted:
	@PYTHONDONTWRITEBYTECODE=1 python3 scripts/check_accepted.py --compile

clean:
	@find . -name "test_runner" -delete
	@find . -name "*.dSYM" -exec rm -rf {} + 2>/dev/null || true
	@echo "Cleaned build artifacts."
