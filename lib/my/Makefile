##
## EPITECH PROJECT, 2025
## makefile
## File description:
## makefile
##
MAKEFLAGS += --no-print-directory

# ─── Project Info ────────────────────────────────────────────────────────
NAME = libmy.a

# ─── Sources ─────────────────────────────────────────────────────────────
SRC	=	print/write_errors.c \
		string/my_strcmp.c \
		string/my_strcpy.c \
		string/my_strlen.c \
		string/my_strncpy.c \
		string/my_str_isnum.c \
		string/my_str_to_word_array.c \
		string/str_to_array_of_word_array.c \
		math/my_getnbr.c \
		memory/free_array_of_word_array.c \
		memory/free_array.c \
		memory/my_strdup.c \
		memory/my_strndup.c \
		io/get_file_size_nostat.c \
		io/openator.c \
		list/push_back.c

# ─── Tools ───────────────────────────────────────────────────────────────
OBJ	= $(SRC:.c=.o)
RM = rm -rf
ECC = epiclang

ifdef DEBUG
OPTFLAGS = -g3
else
OPTFLAGS = -O3
endif

%.o: %.c
	@printf "$(H_BLUE)⚡ $(BOLD)Compiling lib:$(END) $(H_YELLOW)%-45s$(END) $(H_GREEN)[OK]$(END)\r" $<
	@$(ECC) -L../lib -lmy -Wno-unused-command-line-argument $(OPTFLAGS) -c $< -o $@

# ─── Macro: Fancy Header ─────────────────────────────────────────────────
define pretty_header
	@echo "$(BOLD)$(H_PURPLE)╔═══════════════════════════════════════════════════════════════╗$(END)"
	@echo "$(BOLD)$(H_PURPLE)║$(END)$(BOLD)$(WHITE)$(1)$(END)"
	@echo "$(BOLD)$(H_PURPLE)╚═══════════════════════════════════════════════════════════════╝$(END)"
endef

# ─── Rules ───────────────────────────────────────────────────────────────
all:	$(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@printf "                                                                       \r"
	@echo "$(BOLD)$(WHITE) done $(END)"
	$(call pretty_header, 🚀 copying libs 🚀)
	@cp $(NAME) ../
	@mkdir -p ../../include/
	@cp ../Headers/*.h ../../include/
	@echo "$(BOLD)$(WHITE) done $(END)"

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) ../$(NAME)
	@$(RM) -r ../../include

re: fclean all

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
