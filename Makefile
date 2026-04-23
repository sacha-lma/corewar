##
## EPITECH PROJECT, 2025
## makefile
## File description:
## a make file that is able to do lots of things tests manual tests compiling coverage...
## see "make help"
##

MAKEFLAGS += --no-print-directory

# ─── Project Info ────────────────────────────────────────────────────────
 PROJECT = corewar
 NAME	= corewar
 LIB_NAME = libmy.a

# ─── Sources ─────────────────────────────────────────────────────────────
PROG_SRC =	Src/main.c \

# Unit tests are handled by tests/Makefile

# ─── Flags ───────────────────────────────────────────────────────────────
TESTSFLAGS = --coverage -lcriterion -lgcov
LIBSFLAGS = -L ./lib -I ./include -I ./lib/Headers -I ./Src/Headers -lmy -O3 -Wall -Wextra -Werror -Wshadow -Wno-unused-parameter
DEBUGFLAGS = -L ./lib -I ./include -I ./lib/Headers -I ./Src/Headers -lmy -g3 -Wall -Wextra -Werror -Wshadow -Wno-unused-parameter
GCOVRSTYLE = 'github.dark-green'
LOGS_DIR = Logs
COVERAGE_DIR = $(LOGS_DIR)/coverage
COVERAGE_HTML = $(COVERAGE_DIR)/index.html
WEBGCOVRFLAGS = --html-theme $(GCOVRSTYLE) --html --html-nested -o $(COVERAGE_HTML)
GCOVRFLAGS = --gcov-executable "llvm-cov-20 gcov" --exclude tests/
NCURSESFLAGS = -lncurses
MATHSFLAGS = -lm
LIBS = -L ./lib -I ./include -I ./lib/Headers -lmy
CSFMLFLAGS = -lcsfml-graphics -lcsfml-window -lcsfml-system

# ─── Tools ───────────────────────────────────────────────────────────────
RM = rm -rf
ECC = epiclang
CC = clang
ARGUMENTS = Utilities/G-CPE-200_champions/abel.s
DEBUG_STRICT ?= 0
LOCAL_BIN ?= $(HOME)/.local/bin

# ─── random ───────────────────────────────────────────────────────────────
TO_RM = *.gcda *.gcno unit_tests testing *.html *.css *.log main $(LOGS_DIR)
OBJMANU = $(PROG_SRC:.c=.o)


%.o: %.c
	@printf "$(H_CYAN)Compiling$(END) $(BOLD)$<$(END) ... \n"
	@$(ECC) -L./lib -I./include -I./lib/Headers -I./Src/Headers -Wall -Wextra -Werror -Wshadow -Wno-unused-parameter -Wno-unused-command-line-argument -c $< -o $@ 2>&1 > /dev/null && \
		echo "$(BOLD)$(H_GREEN)[ OK ]$(END)" || \
		(echo "$(BOLD)$(H_RED)[ FAIL ]$(END)" && $(ECC) -L./lib -I./include -I./lib/Headers -I./Src/Headers -Wno-unused-command-line-argument -c $< -o $@ && exit 1)

# ─── Macro: Fancy Header ─────────────────────────────────────────────────
define pretty_header
	@echo "$(BOLD)$(H_PURPLE)╔═══════════════════════════════════════════════════════════════╗$(END)"
	@echo "$(BOLD)$(H_PURPLE)║$(END)$(BOLD)$(WHITE)$(1)$(END)"
	@echo "$(BOLD)$(H_PURPLE)╚═══════════════════════════════════════════════════════════════╝$(END)"
endef

# ─── Rules ───────────────────────────────────────────────────────────────
.PHONY: all manu_test run install uninstall debug debug_build valgrind unit_tests tests_run coverage functional_tests clean fclean re banner lib_build lib_build_debug sync_headers
all:	$(NAME) sync_headers

$(NAME): banner | lib_build sync_headers $(OBJMANU)
	@echo ""
	$(call pretty_header, creating binary of : $(PROJECT))
	@$(ECC) -o $(NAME) $(OBJMANU) $(LIBSFLAGS) $(NCURSESFLAGS) $(MATHSFLAGS)
	@echo "$(BOLD)$(WHITE) done $(END)"
	$(call pretty_header, succesfuly compiled $(PROJECT)!)

lib_build:
	@make -C lib/my

lib_build_debug:
	@make -C lib/my DEBUG=1

sync_headers:
	@mkdir -p include
	@if ls lib/Headers/*.h > /dev/null 2>&1; then cp lib/Headers/*.h include/; fi

banner:
	@echo "$(PURPLE)  __  __          _____  ______  __          _______ _______ _    _       _    _ ______          _____ _______   ______     __   _____         _____ _    _          ";
	@echo "$(CYAN) |  \\/  |   /\\   |  __ \\|  ____| \\ \\        / /_   _|__   __| |  | |     | |  | |  ____|   /\\   |  __ \\__   __| |  _ \\ \\   / /  / ____|  /\\   / ____| |  | |   /\\    ";
	@echo "$(PURPLE) | \\  / |  /  \\  | |  | | |__     \\ \\  /\\  / /  | |    | |  | |__| |     | |__| | |__     /  \\  | |__) | | |    | |_) \\ \\_/ /  | (___   /  \\ | |    | |__| |  /  \\   ";
	@echo "$(CYAN) | |\\/| | / /\\ \\ | |  | |  __|     \\ \\/  \\/ /   | |    | |  |  __  |     |  __  |  __|   / /\\ \\ |  _  /  | |    |  _ < \\   /    \\___ \\ / /\\ \\| |    |  __  | / /\\ \\  ";
	@echo "$(PURPLE) | |  | |/ ____ \\| |__| | |____     \\  /\\  /   _| |_   | |  | |  | |     | |  | | |____ / ____ \\| | \\ \\  | |    | |_) | | |     ____) / ____ \\ |____| |  | |/ ____ \\ ";
	@echo "$(CYAN) |_|  |_/_/    \\_\\_____/|______|     \\/  \\/   |_____|  |_|  |_|  |_|     |_|  |_|______/_/    \\_\\_|  \\_\\ |_|    |____/  |_|    |_____/_/    \\_\\_____|_|  |_/_/    \\_\\";
	@echo "$(PURPLE)                                                                                                                                                                   ";
	@echo "$(CYAN)                                                                                                                                                                   ";

manu_test:
	$(call pretty_header, compiling : $(PROJECT))
	@$(ECC) -o $(NAME) $(PROG_SRC) $(LIBSFLAGS)

run:
	$(call pretty_header, running : $(PROJECT))
	@./$(NAME) $(ARGUMENTS)

install: $(NAME)
	@mkdir -p $(LOCAL_BIN)
	@cp $(NAME) $(LOCAL_BIN)/$(NAME)
	@chmod u+x $(LOCAL_BIN)/$(NAME)
	@echo "$(BOLD)$(H_GREEN)Installed$(END) $(NAME) -> $(LOCAL_BIN)/$(NAME)"
	@if ! echo "$(PATH)" | grep -q "$(LOCAL_BIN)"; then \
		echo "$(BOLD)$(H_YELLOW)$(LOCAL_BIN) is not in PATH.$(END)"; \
		echo "Add this to ~/.zshrc:"; \
		echo "  export PATH=\"$(LOCAL_BIN):\$$PATH\""; \
		echo "Then run: source ~/.zshrc && hash -r"; \
	fi

uninstall:
	@rm -f $(LOCAL_BIN)/$(NAME)
	@echo "$(BOLD)$(H_YELLOW)Removed$(END) $(LOCAL_BIN)/$(NAME)"

debug: debug_build valgrind

debug_build: lib_build_debug sync_headers
	$(call pretty_header, compiling with debug flag for : $(PROJECT) )
	@$(ECC) -o $(NAME) $(PROG_SRC) $(DEBUGFLAGS) $(NCURSESFLAGS) $(MATHSFLAGS)
	@echo "$(BOLD)$(WHITE) done $(END)"
	@echo ""
	@echo "$(BOLD)$(H_GREEN)✅ Debug build ready! Time to hunt bugs! 🎯$(END)"
	@echo "$(H_CYAN)Tip: set DEBUG_STRICT=1 to make valgrind exit status fail the target$(END)"

valgrind:
	@echo ""
	@echo "$(H_PURPLE)🔍 Running Valgrind memory check...$(END)"
	@mkdir -p $(LOGS_DIR)
	@VALGRIND_STATUS=0; \
	valgrind --leak-check=full \
	    --show-leak-kinds=all \
	    --track-origins=yes \
	    --log-file=$(LOGS_DIR)/valgrind.log \
		./$(NAME) $(ARGUMENTS) || VALGRIND_STATUS=$$?; \
	echo "$(H_CYAN)📝 Valgrind report saved to $(H_YELLOW)$(LOGS_DIR)/valgrind.log$(END)"; \
	echo ""; \
	if [ -f $(LOGS_DIR)/valgrind.log ] && grep -q "ERROR SUMMARY: 0 errors" $(LOGS_DIR)/valgrind.log; then \
		echo "$(BOLD)$(H_GREEN)✨ No memory errors detected! Perfect! ✨$(END)"; \
	else \
		echo "$(BOLD)$(H_YELLOW)⚠️  Memory issues detected or run interrupted. Check $(LOGS_DIR)/valgrind.log for details$(END)"; \
	fi; \
	if [ $$VALGRIND_STATUS -ne 0 ]; then \
		echo "$(BOLD)$(H_YELLOW)⚠️  Program exited with status $$VALGRIND_STATUS under Valgrind$(END)"; \
	fi; \
	if [ "$(DEBUG_STRICT)" = "1" ] && [ $$VALGRIND_STATUS -ne 0 ]; then exit $$VALGRIND_STATUS; fi
	@echo ""

unit_tests: re
	@$(MAKE) -C tests unit_tests

tests_run: re
	@$(MAKE) -C tests tests_run

coverage: re
	@$(MAKE) -C tests coverage

functional_tests: all
	$(call pretty_header, Running Functional Tests)
	@mkdir -p $(LOGS_DIR)/functional_tests
	@./tests/run_tests.sh; EXIT_CODE=$$?; \
	LATEST="$(LOGS_DIR)/functional_tests/latest.log"; \
	echo ""; \
	echo "$(H_CYAN)\b Functional test report saved to $(H_YELLOW)$$LATEST$(END)"; \
	if [ $$EXIT_CODE -eq 0 ]; then \
		echo "$(BOLD)$(H_GREEN)\b All functional tests passed! \b$(END)"; \
	else \
		echo "$(BOLD)$(H_YELLOW)\b Some tests failed! Check $(H_YELLOW)$(LOGS_DIR)/functional_tests/$(END) for details$(END)"; \
	fi; \
	exit $$EXIT_CODE

clean:
	$(call pretty_header, Cleaning object files)
	@$(RM) $(OBJMANU)
	@make clean -C lib/my/
	@make clean -C tests/

fclean: clean
	$(call pretty_header, Full clean: objects binary tests coverage )
	@$(RM) $(NAME) $(TO_RM) $(name)
	@make fclean -C lib/my/
	@make fclean -C tests/

re: fclean all

#──── optional ─────────────────────────────────────────────────────────────────
.PHONY: help
help:
	@echo ""
	@echo "$(BOLD)$(H_PURPLE)╔═══════════════════════════════════════════════════════════════╗$(END)"
	@echo "$(BOLD)$(H_PURPLE)║$(END)$(BOLD)$(WHITE)   Robot Factory — Corewar Assembler in C                     $(H_PURPLE)║$(END)"
	@echo "$(BOLD)$(H_PURPLE)╚═══════════════════════════════════════════════════════════════╝$(END)"
	@echo ""
	@echo "$(BOLD)$(H_CYAN)Program$(END)"
	@echo "  Binary: $(NAME)"
	@echo "  Usage : ./$(NAME) file.s"
	@echo "  Output: file.cor (Corewar binary, big-endian header and params)"
	@echo ""
	@echo "$(BOLD)$(H_CYAN)Main Targets$(END)"
	@echo "  make / make all             Build libmy + $(NAME)"
	@echo "  make run                    Run ./$(NAME) with ARGUMENTS (default champion)"
	@echo "  make run ARGUMENTS=\"...\"    Run with custom source file"
	@echo "  make manu_test              Quick build command"
	@echo "  make re                     Full rebuild (fclean + all)"
	@echo ""
	@echo "$(BOLD)$(H_CYAN)Install$(END)"
	@echo "  make install                Install $(NAME) to $(LOCAL_BIN)"
	@echo "  make uninstall              Remove $(NAME) from $(LOCAL_BIN)"
	@echo ""
	@echo "$(BOLD)$(H_CYAN)Debug and Analysis$(END)"
	@echo "  make debug                  Debug build + valgrind"
	@echo "  make debug DEBUG_STRICT=1   Fail target if valgrind returns non-zero"
	@echo "  make valgrind               Run valgrind on current ARGUMENTS"
	@echo "  Log: $(LOGS_DIR)/valgrind.log"
	@echo ""
	@echo "$(BOLD)$(H_CYAN)Tests$(END)"
	@echo "  make unit_tests             Build Criterion unit tests"
	@echo "  make tests_run              Run unit tests"
	@echo "  make coverage               Generate coverage HTML report"
	@echo "  make functional_tests       Run assembler functional tests (tests/run_tests.sh)"
	@echo "  Unit logs   : $(LOGS_DIR)/test_output.log"
	@echo "  Func logs   : $(LOGS_DIR)/functional_tests/latest.log"
	@echo "  Coverage log: $(LOGS_DIR)/coverage_report.log"
	@echo ""
	@echo "$(BOLD)$(H_CYAN)Cleanup$(END)"
	@echo "  make clean                  Remove objects"
	@echo "  make fclean                 Remove objects, binary and test artifacts"
	@echo ""
	@echo "$(BOLD)$(H_CYAN)Structure$(END)"
	@echo "  Src/main.c                  CLI entrypoint"
	@echo "  Src/Parser/                 Header parse, body parse, labels/instructions"
	@echo "  Src/Encoder/                Binary encoding and write_cor"
	@echo "  Src/Tools/shifter.c         Big-endian integer conversion"
	@echo "  Src/op.c + Src/Headers/op.h Corewar op table/spec"
	@echo "  lib/my/                     Utility library"
	@echo "  tests/                      Unit + functional tests"
	@echo "  Doc/                        README + architecture diagram"
	@echo ""
	@echo "$(BOLD)$(H_CYAN)Variables$(END)"
	@echo "  ARGUMENTS=$(ARGUMENTS)"
	@echo "  DEBUG_STRICT=$(DEBUG_STRICT)"
	@echo ""


# ─── Styles ──────────────────────────────────────────────────────────────
END = \033[0m
BOLD = \033[1m
ITALICS = \033[3m
UNDER = \033[4m
REV = \033[7m

# ─── Colors ──────────────────────────────────────────────────────────────
GREY = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PURPLE = \033[35m
CYAN = \033[36m
WHITE = \033[37m
H_GREY = \033[90m
H_RED = \033[91m
H_GREEN = \033[92m
H_YELLOW = \033[93m
H_BLUE = \033[94m
H_PURPLE = \033[95m
H_CYAN = \033[96m
H_WHITE = \033[97m

# ─── Background ──────────────────────────────────────────────────────────
B_GREY = \033[40m
B_RED = \033[41m
B_GREEN = \033[42m
B_YELLOW = \033[43m
B_BLUE = \033[44m
B_PURPLE = \033[45m
B_CYAN = \033[46m
B_WHITE = \033[47m
HB_GREY = \033[100m
HB_RED = \033[101m
HB_GREEN = \033[102m
HB_YELLOW = \033[103m
HB_BLUE = \033[104m
HB_PURPLE = \033[105m
HB_CYAN = \033[106m
HB_WHITE = \033[107m
