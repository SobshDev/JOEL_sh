/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

#include "my.h"

int zero_padding_pointer(formatting_t *formatting, int total_chars,
    int padding_chars, int is_null
)
{
    if (formatting->left_justify == 0 && formatting->zero_padding == 1
    && is_null == 0) {
        my_putstr("0x");
        for (int i = 0; i < formatting->width - total_chars; i++) {
            my_putchar('0');
            padding_chars += 1;
        }
    }
    return padding_chars;
}

int formatting_flag_p(formatting_t *formatting, int total_chars,
    int padding_chars, int is_null
)
{
    if (formatting->left_justify == 0 && formatting->zero_padding == 0) {
        for (int i = 0; i < formatting->width - total_chars; i++) {
            my_putchar(' ');
            padding_chars += 1;
        }
    }
    if (formatting->left_justify == 0 && formatting->zero_padding == 1
    && is_null == 1) {
        for (int i = 0; i < formatting->width - total_chars; i++) {
            my_putchar(' ');
            padding_chars += 1;
        }
    }
    return zero_padding_pointer(formatting, total_chars, padding_chars,
    is_null);
}

int left_justify_pointer(formatting_t *formatting, int total_chars,
    int padding_chars
)
{
    if (formatting->left_justify == 1) {
        for (int i = 0; i < formatting->width - total_chars; i++) {
            my_putchar(' ');
            padding_chars += 1;
        }
    }
    return padding_chars;
}

int my_put_pointer_printf(va_list params, formatting_t *formatting)
{
    unsigned long long adress = (unsigned long long)va_arg(params, void *);
    int total_chars = 2 + my_decimal_to_base(adress, 16, 'a', 0);
    int padding_chars = 0;

    if (adress == 0) {
        total_chars = 5;
        padding_chars = formatting_flag_p(formatting, total_chars, 0, 1);
        my_putstr("(nil)");
    } else {
        padding_chars = formatting_flag_p(formatting, total_chars, 0, 0);
        if (formatting->zero_padding == 0)
            my_putstr("0x");
        my_decimal_to_base(adress, 16, 'a', 1);
    }
    padding_chars = left_justify_pointer(formatting, total_chars,
    padding_chars);
    return total_chars + padding_chars;
}
