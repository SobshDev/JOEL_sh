/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

#include "my.h"

int my_print_percent(void)
{
    my_putchar('%');
    return 1;
}

int my_print_percent_printf(va_list params, formatting_t *formatting)
{
    return my_print_percent();
}
