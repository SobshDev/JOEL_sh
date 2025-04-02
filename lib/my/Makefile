##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC = ./my_compute_power_rec.c	\
	./my_revstr.c	\
	./my_put_float.c	\
	./my_str_islower.c	\
	./my_str_isnum.c	\
	./my_print_percent_printf.c	\
	./get_formatting.c	\
	./my_find_prime_sup.c	\
	./my_str_isprintable.c	\
	./my_swap.c	\
	./my_showmem.c	\
	./my_showstr.c	\
	./print_current_chars.c	\
	./my_str_to_word_array.c	\
	./my_put_float_printf.c	\
	./my_strupcase.c	\
	./my_put_nbr_printf.c	\
	./my_decimal_to_base.c	\
	./my_sort_int_array.c	\
	./my_is_prime.c	\
	./my_strcat.c	\
	./my_strstr.c	\
	./my_strncmp_printf.c	\
	./my_putstr.c	\
	./my_put_nbr.c	\
	./my_isneg.c	\
	./my_strncmp.c	\
	./my_getnbr.c	\
	./my_str_isalpha.c	\
	./my_str_isupper.c	\
	./my_show_word_array.c	\
	./my_strdup.c	\
	./my_strncpy.c	\
	./my_strcapitalize.c	\
	./my_strlowcase.c	\
	./my_strlen.c	\
	./my_compute_square_root.c	\
	./my_printf.c	\
	./my_strncat.c	\
	./my_putchar_printf.c	\
	./my_strcmp.c	\
	./my_strcpy.c	\
	./my_putchar.c	\
	./my_scientific_notation.c	\
	./my_putstr_printf.c	\
	./my_put_unsigned_nbr.c	\
	./my_put_pointer.c	\
	./formatting_put_nbr.c	\
	./my_flag_g.c	\
	./display_flag_g.c	\
	./formatting_flag_g.c	\
	./flag_a.c	\
	./count_digits.c	\
	./my_putstr_err.c

OBJ = $(SRC:.c=.o)

NAME = libmy.a

all: $(NAME)

$(NAME): $(OBJ)
	@ar	rc	$(NAME)	$(OBJ)
	@cp	my.h	../../include
	@mv	$(NAME)	../

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) ../$(NAME)

re: fclean all
