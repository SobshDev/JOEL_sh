/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** my_put_unsigned_nbr
*/

#include "my.h"

int my_put_unsigned_nbr(long long unsigned int nb, int prev_count)
{
    long long unsigned int temp_nb = nb;
    int count = prev_count;

    count++;
    if (temp_nb < 10)
        my_putchar(temp_nb + '0');
    else {
        count = my_put_unsigned_nbr(temp_nb / 10, count);
        my_putchar((temp_nb % 10) + '0');
    }
    return count;
}

long long unsigned count_digit(long long unsigned nb)
{
    if (nb / 10 == 0)
        return 1;
    return 1 + count_digit(nb / 10);
}

int right_padding(formatting_t *formatting, long long unsigned int total,
    int i
)
{
    if (formatting->left_justify == 0 && formatting->width > total
        && formatting->zero_padding == 0) {
        for (i = 0; i < formatting->width - total; i++) {
            my_putchar(' ');
        }
    }
    if (formatting->left_justify == 0 && formatting->width > total
        && formatting->zero_padding == 1) {
        for (i = 0; i < formatting->width - total; i++) {
            my_putchar('0');
        }
    }
    return i;
}

int my_put_unsigned_nbr_printf(va_list params, formatting_t *formatting)
{
    long long unsigned int total = 0;
    long long unsigned int number = va_arg(params, long long unsigned int);
    int i = 0;

    total = count_digit(number);
    i = right_padding(formatting, total, i);
    my_put_unsigned_nbr(number, 0);
    if (formatting->left_justify == 1 && formatting->width > total) {
        for (i = 0; i < formatting->width - total; i++) {
            my_putchar(' ');
        }
    }
    return total + i;
}
