/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

#include "my.h"

int hardcode(double number, int precision, int hashtag, char e)
{
    if (!hashtag) {
        if (number > 0.1 && number < 1)
            precision = 2;
        if (number > 0.01 && number < 0.1)
            precision = 3;
        if (number > 0.001 && number < 0.01)
            precision = 4;
        if (number > 0.0001 && number < 0.001)
            precision = 5;
    } else {
        if (number > 0.1 && number < 1)
            precision = 6;
        if (number > 0.01 && number < 0.1)
            precision = 7;
        if (number > 0.001 && number < 0.01)
            precision = 8;
        if (number > 0.0001 && number < 0.001)
            precision = 9;
    }
    return my_put_float(number, precision, e, 1);
}

int flag_g_bis_with_hashtag(double number, int precision, int hashtag, char e)
{
    for (int i = -4; i < precision; i++) {
        if (i < 0 && number < 1)
            return hardcode(number, precision, hashtag, e);
        if (i == 0 && 1 <= number && number < 10) {
            precision -= 1;
            break;
        }
        if (i > 0 && number > my_pow(10, i) && number < my_pow(10, i + 1)) {
            precision = precision - i - 1;
            break;
        }
    }
    return my_put_float(number, precision, e, 1);
}

int flag_g_bis_no_hashtag(double number, int precision, int hashtag, char e)
{
    for (int i = -4; i <= 1; i++) {
        if (i < 0 && number < 1)
            return hardcode(number, precision, hashtag, e);
        if (i == 0 && 1 <= number && number < 10) {
            precision = 1;
            break;
        }
        if (i > 0) {
            precision = 0;
            break;
        }
    }
    return my_put_float(number, precision, e, 1);
}

int flag_g(double number, int precision, char e, int hashtag)
{
    int tool = precision;

    if (number < 0) {
        my_putchar('-');
        number *= -1;
    }
    if (precision > 1 && !hashtag)
        tool = 2;
    if (precision < 1 && !hashtag)
        tool = 1;
    if (number < 0.0001)
        return my_sci_notation(number, e, tool - 1, 1);
    if (number >= my_pow(10, precision))
        return my_sci_notation(number, e, tool - 1, 1);
    else {
        if (hashtag)
            return flag_g_bis_with_hashtag(number, precision, hashtag, e);
        else
            return flag_g_bis_no_hashtag(number, precision, hashtag, e);
    }
}
