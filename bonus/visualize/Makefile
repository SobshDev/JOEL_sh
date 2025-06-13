##
## EPITECH PROJECT, 2025
## Minishell 2
## File description:
## Makefile
##

CPPFLAGS = -I ../../include/
CFLAGS = -Wall -Wextra -Werror -W -g3
LFLAGS = -L ../../lib/ -lmy
SRC = $(shell find ../../src/ -name '*.c' -not -name 'main.c')	\
	view_main.c	\
	print_ast.c
OBJ = $(SRC:.c=.o)
NAME = 42sh_view


all: $(NAME)

$(NAME): $(OBJ)
	make -C ../../lib/my
	$(CC) $(OBJ) -o $(NAME) $(LFLAGS) $(CFLAGS) $(CPPFLAGS)

clean:
	make clean -C ../../lib/my
	$(RM) $(OBJ)

fclean: clean
	make fclean -C ../../lib/my
	$(RM) $(NAME)

re: fclean all

run:
	@make -sj all; true
	@./$(NAME) || true
	@make -s fclean

.PHONY: all clean fclean re run
