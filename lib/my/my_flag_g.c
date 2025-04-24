/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** my_flag_g
*/

#include "my.h"

int hardcode_count(double number, int precision, int hashtag, char e)
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
    return my_put_float(number, precision, e, 0);
}

int flag_g_bis_with_hashtag_count(double number, int precision, int hashtag,
    char e
)
{
    for (int i = -4; i < precision; i++) {
        if (i < 0 && number < 1)
            return hardcode_count(number, precision, hashtag, e);
        if (i == 0 && 1 <= number && number < 10) {
            precision -= 1;
            break;
        }
        if (i > 0 && number > my_pow(10, i) && number < my_pow(10, i + 1)) {
            precision = precision - i - 1;
            break;
        }
    }
    return my_put_float(number, precision, e, 0);
}

int flag_g_bis_no_hashtag_count(double number, int precision, int hashtag,
    char e
)
{
    for (int i = -4; i <= 1; i++) {
        if (i < 0 && number < 1)
            return hardcode_count(number, precision, hashtag, e);
        if (i == 0 && 1 <= number && number < 10) {
            precision = 1;
            break;
        }
        if (i > 0) {
            precision = 0;
            break;
        }
    }
    return my_put_float(number, precision, e, 0);
}

int flag_g_count(double number, int precision, char e, int hashtag)
{
    int tool = precision;

    if (number < 0)
        number *= -1;
    if (precision > 1 && !hashtag)
        tool = 2;
    if (precision < 1 && !hashtag)
        tool = 1;
    if (number < 0.0001)
        return my_sci_notation(number, e, tool - 1, 0);
    if (number >= my_pow(10, precision))
        return my_sci_notation(number, e, tool - 1, 0);
    else {
        if (hashtag)
            return flag_g_bis_with_hashtag_count(number, precision, hashtag,
            e);
        else
            return flag_g_bis_no_hashtag_count(number, precision, hashtag, e);
    }
}

int flag_g_printf(va_list params, formatting_t *formatting)
{
    double value = va_arg(params, double);
    char c = formatting->c - 2;
    int total_chars = flag_g_count(value, formatting->precision, c,
    formatting->hexa_prefix) + 1;
    int padding_chars = 0;

    if (formatting->left_justify == 0 && formatting->zero_padding == 0) {
        padding_chars = space_formatting_g(total_chars, padding_chars,
        formatting);
    }
    zero_padding_g(formatting, total_chars, &padding_chars, &value);
    flag_g(value, formatting->precision, c, formatting->hexa_prefix);
    if (formatting->left_justify == 1) {
        padding_chars = space_formatting_g(total_chars, padding_chars,
        formatting);
    }
    return total_chars + padding_chars;
}
