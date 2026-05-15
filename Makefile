##
## EPITECH PROJECT, 2026
## corewar
## File description:
## Makefile
##
NAME	= corewar

CC	= epiclang
CFLAGS	= -Wall -Wextra -Werror -Wshadow -Wunreachable-code -Wno-unused-parameter\
	-Wuninitialized -Wnull-dereference -O3
IFLAGS	= -I include

SRCS	= $(shell find src/ -name "*.c")
OBJS	= $(SRCS:.c=.o)

LOG_DIR	= log

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

ARGS	= tests/tests_files/abel.cor -n 6 tests/tests_files/abel.cor tests/tests_files/abel.cor tests/tests_files/abel.cor > output

debug: CFLAGS += -g3
debug: fclean $(NAME)
	@mkdir -p $(LOG_DIR)
	valgrind --leak-check=full --track-origins=yes \
		--log-file=$(LOG_DIR)/valgrind.log ./$(NAME) $(ARGS)

tests_run: re
	@echo "No tests defined yet"

clean:
	rm -rf $(OBJS) log output

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug tests_run
