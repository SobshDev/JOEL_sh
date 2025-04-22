/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** my_baltrou
*/

#include "my.h"

int display(double number, char e, int exponent)
{
    my_putchar(e);
    if (exponent < 0) {
        my_putchar('-');
        exponent *= -1;
    } else
        my_putchar('+');
    if (exponent < 10)
        my_put_nbr(0);
    my_put_nbr(exponent);
    return 0;
}

void get_exponent(double *number, int *i, int is_smol)
{
    while (1 > *number || 10 < *number) {
        if (is_smol) {
            *number *= 10;
            (*i)--;
        } else {
            *number /= 10;
            (*i)++;
        }
    }
}

int my_sci_notation(double number, char e, int precision, int is_display)
{
    int is_smol = 0;
    int i = 0;
    int total = 0;

    if (number < 0){
        number *= -1;
        if (is_display)
            my_putchar('-');
    }
    if (number < 1)
        is_smol = 1;
    get_exponent(&number, &i, is_smol);
    total += my_put_float(number, precision, e, is_display);
    if (is_display)
        display(number, e, i);
    return total + 4;
}

int padding(formatting_t *formatting, int total_chars, int padding_chars)
{
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

int my_sci_notation_printf(va_list params, formatting_t *formatting)
{
    double number = va_arg(params, double);
    int total_chars = my_sci_notation(number, formatting->c,
    formatting->precision, 0);
    int padding_chars = padding(formatting, total_chars, padding_chars);

    my_sci_notation(number, formatting->c, formatting->precision, 1);
    if (formatting->left_justify == 1) {
        for (int i = 0; i < formatting->width - total_chars; i++) {
            my_putchar(' ');
            padding_chars += 1;
        }
    }
    return total_chars + padding_chars;
}
