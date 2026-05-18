##
## EPITECH PROJECT, 2026
## corewar
## File description:
## Bonus — CSFML visualizer (corewar_visu)
##

NAME    = corewar_visu
CC      = gcc
CFLAGS  = -Wall -Wextra -Wno-unused-parameter -Wno-unused-result \
          -Wno-builtin-declaration-mismatch -O2
IFLAGS  = -I include -I ../include
LFLAGS  = -lcsfml-graphics -lcsfml-window -lcsfml-system

CORE_SRCS = $(filter-out ../src/core/main.c, \
              $(shell find ../src -name "*.c"))
VISU_SRCS = $(shell find src/ -name "*.c")

CORE_OBJS = $(patsubst ../src/%.c, obj/core/%.o, $(CORE_SRCS))
VISU_OBJS = $(patsubst src/%.c,    obj/visu/%.o, $(VISU_SRCS))
OBJS      = $(CORE_OBJS) $(VISU_OBJS)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

obj/core/%.o: ../src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

obj/visu/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

run: all
	./$(NAME) $(ARGS)

clean:
	rm -rf obj/

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re run
