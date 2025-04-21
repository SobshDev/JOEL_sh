/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

#include "my.h"

int hardcoded_printf(int is_display)
{
    if (is_display == 1)
        my_putstr("-2147483648");
    return 11;
}

int put_nbr_printf(int nb, int prev_count, formatting_t *formatting,
    int is_display
)
{
    int count = prev_count;

    if (nb == -2147483648)
        return hardcoded_printf(is_display);
    if (nb < 0) {
        if (is_display == 1)
            my_putchar('-');
        count += 1;
        nb = nb * (-1);
    }
    if (nb < 10) {
        if (is_display == 1)
            my_putchar(nb + '0');
    } else {
        count = put_nbr_printf(nb / 10, count, formatting, is_display);
        count += 1;
        if (is_display == 1)
            my_putchar((nb % 10) + '0');
    }
    return count;
}

int my_put_nbr_printf(va_list params, formatting_t *formatting)
{
    int padding_chars = 0;
    int number = va_arg(params, int);
    int total = put_nbr_printf(number, 1, formatting, 0);

    formatting->width -= formatting->space;
    if (formatting->show_sign == 1 && number >= 0)
        total += 1;
    if (space_flag(formatting, number) == 1)
        return total + 1;
    if (formatting->left_justify == 0 && formatting->zero_padding == 0)
        padding_chars += space_padding(total, formatting, padding_chars);
    if (formatting->left_justify == 0 && formatting->zero_padding == 1)
        zero_padding(&number, formatting, total, &padding_chars);
    if (formatting->show_sign == 1 && number >= 0
    && formatting->zero_padding == 0)
        my_putchar('+');
    put_nbr_printf(number, 1, formatting, 1);
    if (formatting->left_justify == 1)
        padding_chars += left_padding_putnbr(total, formatting, padding_chars);
    return total + padding_chars;
}
