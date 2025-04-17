/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

#include "my.h"

int space_padding(int total, formatting_t *formatting, int padding_chars)
{
    for (int i = 0; i < formatting->width - total; i++) {
        my_putchar(' ');
        padding_chars += 1;
    }
    return padding_chars;
}

int zero_padding(int *number, formatting_t *formatting, int total,
    int *padding_chars
)
{
    if (formatting->show_sign == 1 && *number >= 0)
        my_putchar('+');
    if (*number < 0) {
        my_putchar('-');
        (*number) *= -1;
    }
    for (int i = 0; i < formatting->width - total; i++) {
        my_putchar('0');
        *padding_chars += 1;
    }
}

int left_padding_putnbr(int total, formatting_t *formatting, int padding_chars)
{
    for (int i = 0; i < formatting->width - total; i++) {
        my_putchar(' ');
        padding_chars += 1;
    }
    return padding_chars;
}

int space_flag(formatting_t *formatting, int number)
{
    if (formatting->space == 1 && number >= 0) {
        my_putchar(' ');
        put_nbr_printf(number, 1, formatting, 1);
        return 1;
    } else
        return 0;
}
