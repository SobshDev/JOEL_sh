/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

#include "my.h"

int putstr_printf(char const *str, formatting_t *formatting)
{
    int i = 0;
    int j = 0;
    int k = 0;

    if (formatting->left_justify == 0) {
        for (i = 0; i < formatting->width - my_strlen(str); i++)
            my_putchar(' ');
    }
    for (j = 0; str[j] != '\0'; j++)
        my_putchar(str[j]);
    if (formatting->left_justify == 1) {
        for (k = 0; k < formatting->width - my_strlen(str); k++)
            my_putchar(' ');
    }
    return i + j + k;
}

int putstr_printf_precision(char const *str, formatting_t *formatting)
{
    int i = 0;
    int j = 0;
    int k = 0;

    if (formatting->left_justify == 0) {
        for (i = 0; i < formatting->width - formatting->precision; i++)
            my_putchar(' ');
    }
    for (j = 0; j != formatting->precision; j++)
        my_putchar(str[j]);
    if (formatting->left_justify == 1) {
        for (k = 0; k < formatting->width - formatting->precision; k++)
            my_putchar(' ');
    }
    return i + j + k;
}

int my_putstr_printf(va_list params, formatting_t *formatting)
{
    char *str = va_arg(params, char *);

    if (str == NULL)
        str = "(null)";
    if (formatting->star == false && formatting->precision == -1)
        return putstr_printf(str, formatting);
    if (formatting->star == true && formatting->precision == -1)
        return putstr_printf(str, formatting);
    if (formatting->star == false && formatting->precision != -1)
        return putstr_printf_precision(str, formatting);
    if (formatting->star == true && formatting->precision != -1)
        return putstr_printf_precision(str, formatting);
}
