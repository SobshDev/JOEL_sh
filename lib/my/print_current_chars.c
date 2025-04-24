/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

#include "my.h"

int print_current_chars(va_list params, formatting_t *formatting)
{
    int *total = va_arg(params, int *);

    *total = formatting->total_chars;
    return 0;
}
