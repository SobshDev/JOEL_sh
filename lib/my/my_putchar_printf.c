/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

#include "my.h"

void putchar_printf(char c)
{
    write(1, &c, 1);
}

int my_putchar_printf(va_list params, formatting_t *formatting)
{
    int padding_chars = 0;

    if (formatting->left_justify == 0) {
        for (int i = 0; i < formatting->width - 1; i++) {
            my_putchar(' ');
            padding_chars += 1;
        }
    }
    putchar_printf(va_arg(params, int));
    if (formatting->left_justify == 1) {
        for (int i = 0; i < formatting->width - 1; i++) {
            my_putchar(' ');
            padding_chars += 1;
        }
    }
    return 1 + padding_chars;
}
