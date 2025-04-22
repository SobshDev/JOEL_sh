/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

#include "my.h"


int my_put_float_count(double number, int precision)
{
    int count = 0;
    int part = (int)number;
    double nb = number - (double)part;

    if (part == 0)
        count += 1;
    for (count; part > 0; count++)
        part /= 10;
    if (precision == 0)
        return count + 1;
    return count + precision + 1;
}

int my_put_float_formatting(formatting_t *formatting, int total_chars)
{
    int padding_chars = 0;

    if (formatting->left_justify == 0 && formatting->zero_padding == 0) {
        for (int i = 0; i < formatting->width - total_chars; i++) {
            my_putchar(' ');
            padding_chars += 1;
        }
    }
    if (formatting->left_justify == 0 && formatting->zero_padding == 1) {
        for (int i = 0; i < formatting->width - total_chars; i++) {
            my_putchar('0');
            padding_chars += 1;
        }
    }
    return padding_chars;
}

int my_put_float_printf(va_list params, formatting_t *formatting)
{
    double number = va_arg(params, double);
    int precision = formatting->precision;
    int total_chars = my_put_float_count(number, precision);
    int padding_chars = 0;

    if (precision == 0)
        formatting->width += 1;
    padding_chars = my_put_float_formatting(formatting, total_chars);
    my_put_float(number, precision, formatting->c, 1);
    if (formatting->left_justify == 1) {
        for (int i = 0; i < formatting->width - total_chars; i++) {
            my_putchar(' ');
            padding_chars += 1;
        }
    }
    return total_chars + padding_chars;
}
