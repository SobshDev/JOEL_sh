/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

#include "my.h"

my_printf_t const DISPLAY[] = {
    {"d", my_put_nbr_printf},
    {"i", my_put_nbr_printf},
    {"s", my_putstr_printf},
    {"c", my_putchar_printf},
    {"%", my_print_percent_printf},
    {"x", my_decimal_to_base_printf},
    {"b", my_decimal_to_base_printf},
    {"o", my_decimal_to_base_printf},
    {"X", my_decimal_to_base_printf},
    {"n", print_current_chars},
    {"ld", my_put_nbr_printf},
    {"f", my_put_float_printf},
    {"F", my_put_float_printf},
    {"u", my_put_unsigned_nbr_printf},
    {"lu", my_put_unsigned_nbr_printf},
    {"llu", my_put_unsigned_nbr_printf},
    {"e", my_sci_notation_printf},
    {"E", my_sci_notation_printf},
    {"p", my_put_pointer_printf},
    {"g", flag_g_printf},
    {"G", flag_g_printf},
    {0, NULL}
};

void add_size_of_flag(int size, int *i)
{
    if (size > 1)
        (*i) += size - 1;
}

int get_precision(char const *format, int *i, va_list params,
    formatting_t *formatting
)
{
    if (format[*i] == '.') {
        (*i) += 1;
        if (format[*i] == '*') {
            formatting->precision = va_arg(params, int);
            formatting->star = true;
            (*i) += 1;
        } else
            formatting->precision = get_width(format, i);
    }
}

int display_flags(char const *format, int *i, va_list params, int total_chars)
{
    formatting_t formatting = {0, 0, 0, 0, 0, -1, 0, 0, 0, false};
    int size = 0;

    (*i) += 1;
    get_formatting(format, i, &formatting, params);
    get_precision(format, i, params, &formatting);
    for (int j = 0; DISPLAY[j].flag != NULL; j++) {
        size = my_strlen(DISPLAY[j].flag);
        if (my_strncmp_printf(DISPLAY[j].flag, &format[*i], size) == 0) {
            formatting.c = format[*i];
            formatting.total_chars = total_chars;
            total_chars += DISPLAY[j].display(params, &formatting);
            add_size_of_flag(size, i);
        }
    }
    return total_chars;
}

int my_printf(char const *format, ...)
{
    va_list params;
    int total_chars = 0;

    va_start(params, format);
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            total_chars = display_flags(format, &i, params, total_chars);
        } else {
            my_putchar(format[i]);
            total_chars += 1;
        }
    }
    va_end(params);
    return 0;
}
