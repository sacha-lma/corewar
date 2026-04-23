##
## EPITECH PROJECT, 2025
## tests/Makefile
## File description:
## Dedicated Makefile for Criterion unit tests
##

MAKEFLAGS += --no-print-directory

# ─── Sources ─────────────────────────────────────────────────────────────
SRCTST =	unit_tests_robotfactory.c \
			../Src/op.c \
			../Src/Tools/shifter.c \
			../Src/Parser/parser.c \
			../Src/Parser/is_header_line.c \
			../Src/Parser/get_opcode.c \
			../Src/Parser/get_instr_size.c \
			../Src/Parser/free_robotfactory.c \
			../Src/Parser/validate_instr.c \
			../Src/Parser/parser_body.c \
			../Src/Encoder/encoder.c

# ─── Flags ───────────────────────────────────────────────────────────────
CC = clang
RM = rm -rf
TESTSFLAGS = --coverage -lcriterion -lgcov
LIBSFLAGS = -L ../lib -I ../include -I ../lib/Headers -I ../Src/Headers -lmy -O3 -Wall -Wextra -Werror -Wshadow -Wno-unused-parameter
MATHSFLAGS = -lm
GCOVRSTYLE = 'github.dark-green'
LOGS_DIR = ../Logs
COVERAGE_DIR = $(LOGS_DIR)/coverage
COVERAGE_RAW_DIR = $(COVERAGE_DIR)/raw
COVERAGE_HTML = $(COVERAGE_DIR)/index.html
WEBGCOVRFLAGS = --html-theme $(GCOVRSTYLE) --html --html-nested -o $(COVERAGE_HTML)
GCOVRFLAGS = --gcov-executable "llvm-cov-20 gcov" --exclude tests/ --root ..

# ─── Colors ──────────────────────────────────────────────────────────────
END = \033[0m
BOLD = \033[1m
H_GREEN = \033[92m
H_YELLOW = \033[93m

# ─── Rules ───────────────────────────────────────────────────────────────
.PHONY: all unit_tests tests_run coverage clean fclean

all: unit_tests

unit_tests:
	@mkdir -p $(LOGS_DIR) $(COVERAGE_RAW_DIR)
	@$(CC) -o unit_tests $(SRCTST) $(TESTSFLAGS) $(LIBSFLAGS) $(MATHSFLAGS)

tests_run: unit_tests
	@CRITERION_SHOW_STDOUT=1 ./unit_tests > $(LOGS_DIR)/test_output.log 2>&1; EXIT_CODE=$$?; \
	if [ $$EXIT_CODE -ne 0 ]; then \
		echo "$(BOLD)$(H_YELLOW)⚠️  Some tests failed! Check $(LOGS_DIR)/test_output.log for details. ⚠️$(END)"; \
		cat $(LOGS_DIR)/test_output.log; \
		exit $$EXIT_CODE; \
	fi; \
	echo "$(BOLD)$(H_GREEN)✅ All tests passed! Generating coverage report...$(END)"; \
	gcovr $(GCOVRFLAGS) $(WEBGCOVRFLAGS) > $(LOGS_DIR)/coverage_report.log 2>&1; \
	gcovr $(GCOVRFLAGS) --branches >> $(LOGS_DIR)/coverage_report.log 2>&1; \
	echo "$(BOLD)$(H_GREEN)✅ Tests executed and coverage report generated! Check $(LOGS_DIR)/test_output.log and $(LOGS_DIR)/coverage_report.log for details. 🎉$(END)"

coverage: unit_tests
	@mkdir -p $(LOGS_DIR) $(COVERAGE_RAW_DIR)
	@./unit_tests
	@gcovr $(GCOVRFLAGS) $(WEBGCOVRFLAGS)
	@gcovr $(GCOVRFLAGS) --txt-metric branch
	@xdg-open $(COVERAGE_HTML)

clean:
	@$(RM) unit_tests *.gcda *.gcno

fclean: clean

