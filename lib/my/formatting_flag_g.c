/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

#include "my.h"

void zero_padding_g(formatting_t *formatting, int total_chars,
    int *padding_chars, double *value
)
{
    if (formatting->left_justify == 0 && formatting->zero_padding == 1) {
        if (*value < 0) {
            my_putchar('-');
            (*value) *= -1;
        }
        for (int i = 0; i < formatting->width - total_chars; i++) {
            my_putchar('0');
            *padding_chars += 1;
        }
    }
}

int space_formatting_g(int total_chars, int padding_chars,
    formatting_t *formatting
)
{
    for (int i = 0; i < formatting->width - total_chars; i++) {
        my_putchar(' ');
        padding_chars += 1;
    }
    return padding_chars;
}
