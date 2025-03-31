##
## EPITECH PROJECT, 2025
## Minishell 2
## File description:
## Makefile
##

CPPFLAGS = -Iinclude/
CFLAGS = -Wall -Wextra -Werror -W -g3
LFLAGS = -L lib/ -lmy
SRC = $(shell find src/ -name '*.c' -not -name 'view_main.c')
OBJ = $(SRC:.c=.o)
NAME = 42sh

all: $(NAME)

$(NAME): $(OBJ)
	make -C lib/my
	$(CC) $(OBJ) -o $(NAME) $(LFLAGS) $(CFLAGS) $(CPPFLAGS)

clean:
	make clean -C lib/my
	$(RM) $(OBJ)

fclean: clean
	make fclean -C lib/my
	$(RM) $(NAME)

re: fclean all

run:
	@make -sj all; true
	@(./$(NAME) ; echo "Exit code: $$?") || true
	@make -s fclean

test:
	@make -s all; true
	@./tests/tester.sh || true
	@make -s fclean

view:
	@make -s run -C bonus/visualize

.PHONY: all clean fclean re run view
