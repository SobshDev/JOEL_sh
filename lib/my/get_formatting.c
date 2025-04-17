/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

#include "my.h"

int get_width(char const *format, int *i)
{
    int width = 0;

    while (format[*i] >= '0' && format[*i] <= '9') {
        width = width * 10 + (format[*i] - '0');
        (*i) += 1;
    }
    if (width == 0)
        return -1;
    return width;
}

void get_formatting_bis(char const *format, int *i, formatting_t *formatting,
    va_list params
)
{
    if (format[*i] == ' ') {
        formatting->space = 1;
        (*i) += 1;
    }
    if (format[*i] == '#') {
        formatting->hexa_prefix = 1;
        (*i) += 1;
    }
    if (format[*i] == '*') {
        formatting->width = va_arg(params, int);
        (*i) += 1;
    }
    if (format[*i] >= '0' && format[*i] <= '9')
        formatting->width = get_width(format, i);
}

void get_formatting(char const *format, int *i, formatting_t *formatting,
    va_list params
)
{
    if (format[*i] == '#') {
        formatting->hexa_prefix = 1;
        (*i) += 1;
    }
    if (format[*i] == '-') {
        formatting->left_justify = 1;
        (*i) += 1;
    }
    if (format[*i] == '+') {
        formatting->show_sign = 1;
        (*i) += 1;
    }
    if (format[*i] == '0') {
        formatting->zero_padding = 1;
        (*i) += 1;
    }
    get_formatting_bis(format, i, formatting, params);
}
