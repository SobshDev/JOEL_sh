/*
** EPITECH PROJECT, 2024
** printf
** File description:
** my_my_decimal_to_hexa
*/

#include "my.h"

static int display_reverse(int display, int i, char *result)
{
    if (display == 1) {
        for (int k = i - 1; k >= 0; k--)
            my_putchar(result[k]);
    }
    return my_strlen(result);
}

int my_decimal_to_base(unsigned long long number, int base, char c,
    int display
)
{
    char result[64];
    int remainder = 0;
    int i = 0;

    for (int j = 0; j < 64; j++)
        result[j] = '\0';
    for (i = 0; number > 0; i++) {
        remainder = number % base;
        if (remainder < 10)
            result[i] = remainder + '0';
        else
            result[i] = remainder + c - 10;
        number = number / base;
    }
    return display_reverse(display, i, result);
}

int get_len(int number, formatting_t *formatting)
{
    int total_chars = 0;

    if (formatting->hexa_prefix == 1) {
        if (formatting->c != 'o')
            total_chars += 1;
        total_chars += 1;
    }
    if (formatting->c == 'x')
        total_chars += my_decimal_to_base(number, 16, 'a', 0);
    if (formatting->c == 'b')
        total_chars += my_decimal_to_base(number, 2, 'a', 0);
    if (formatting->c == 'o')
        total_chars += my_decimal_to_base(number, 8, 'a', 0);
    if (formatting->c == 'X')
        total_chars += my_decimal_to_base(number, 16, 'A', 0);
    return total_chars;
}

int print_number_with_padding(int number, formatting_t *formatting,
    int total_chars
)
{
    int padding_chars = 0;

    if (formatting->c == 'x')
        my_decimal_to_base(number, 16, 'a', 1);
    if (formatting->c == 'b')
        my_decimal_to_base(number, 2, 'a', 1);
    if (formatting->c == 'o')
        my_decimal_to_base(number, 8, 'a', 1);
    if (formatting->c == 'X')
        my_decimal_to_base(number, 16, 'A', 1);
    if (formatting->left_justify == 1) {
        for (int i = 0; i < formatting->width - total_chars; i++) {
            my_putchar(' ');
            padding_chars += 1;
        }
    }
    return padding_chars;
}

int left_padding(int total_chars, formatting_t *formatting)
{
    int padding_chars = 0;

    if (formatting->left_justify == 0 && formatting->zero_padding == 0) {
        for (int i = 0; i < formatting->width - total_chars; i++) {
            my_putchar(' ');
            padding_chars += 1;
        }
    }
    if (formatting->hexa_prefix == 1) {
        my_putchar('0');
        if (formatting->c != 'o')
            my_putchar(formatting->c);
    }
    if (formatting->left_justify == 0 && formatting->zero_padding == 1) {
        for (int i = 0; i < formatting->width - total_chars; i++) {
            my_putchar('0');
            padding_chars += 1;
        }
    }
    return padding_chars;
}

int my_decimal_to_base_printf(va_list params, formatting_t *formatting)
{
    int number = va_arg(params, int);
    int total_chars = 0;
    int padding_chars = 0;

    if (number == 0) {
        my_putchar('0');
        return 1;
    }
    total_chars = get_len(number, formatting);
    padding_chars += left_padding(total_chars, formatting);
    padding_chars += print_number_with_padding(number, formatting,
    total_chars);
    return total_chars + padding_chars;
}
