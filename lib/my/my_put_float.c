/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** my_put_float
*/

#include "my.h"

int handle_nan(double number, char c, int is_display)
{
    if (number != number) {
        if (c >= 'a' && c <= 'z' && is_display)
            my_putstr("-nan");
        if (c >= 'A' && c <= 'Z' && is_display)
            my_putstr("-NAN");
        return 4;
    }
}

int handle_inf(double number, char c, int is_display)
{
    if (number == 1.0 / 0.0) {
        if (c >= 'a' && c <= 'z' && is_display)
            my_putstr("inf");
        if (c >= 'A' && c <= 'Z' && is_display)
            my_putstr("INF");
        return 3;
    }
}

int handle_errors(double number, char c, int is_display)
{
    if (handle_inf(number, c, is_display) == 3)
        return 3;
    if (handle_nan(number, c, is_display) == 4)
        return 4;
    return 0;
}

int display_floating_part(int precision, double nb)
{
    for (int i = 0; i < precision; i++) {
        nb *= 10;
        if (nb == 0)
            my_put_nbr(0);
        else
            my_put_nbr((int)nb);
        nb -= (int)nb;
    }
}

int my_put_float(double number, int precision, char c, int is_display)
{
    int count = 0;
    int part = (int)number;
    double nb = number - (double)part;
    int error = handle_errors(number, c, is_display);

    if (error != 0)
        return error;
    if (is_display)
        my_put_nbr(part);
    for (count; part > 0; count++)
        part /= 10;
    if (precision == 0)
        return count;
    if (is_display)
        my_putchar('.');
    if (is_display)
        display_floating_part(precision, nb);
    return count + precision + 1;
}
