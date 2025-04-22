/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

#include "my.h"

int hardcoded_printf(void)
{
    my_putstr("9223372036854775808");
    return 11;
}

int put_long_nbr_printf(long int nb, int prev_count, formatting_t *formatting)
{
    long int temp_nb = nb;
    int count = prev_count;

    if (temp_nb < 0) {
        formatting->width -= 1;
        count = padding(prev_count, formatting, count, nb);
        count += 1;
        temp_nb = temp_nb * (-1);
    } else
        count = padding(prev_count, formatting, count, nb);
    if (temp_nb == -2147483648)
        return hardcoded_printf();
    if (temp_nb < 10) {
        my_putchar(temp_nb + '0');
    } else {
        count = put_long_nbr_printf(temp_nb / 10, count, formatting);
        count += 1;
        my_putchar((temp_nb % 10) + '0');
    }
    return count;
}

int my_put_long_nbr_printf(va_list params, formatting_t *formatting)
{
    int total = 0;
    int i = 0;

    formatting->width -= formatting->space;
    total = put_long_nbr_printf(va_arg(params, int), 1, formatting);
    if (formatting->left_justify == 1 && formatting->width > total) {
        for (i = 0; i < formatting->width - total; i++) {
            my_putchar(' ');
        }
    }
    return total + i;
}
