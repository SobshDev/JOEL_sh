/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** flag_a
*/

#include "my.h"

static int count_digit(int nb)
{
    if (nb / 10 == 0)
        return 1;
    return 1 + count_digit(nb / 10);
}

static int make_it_positive(double number)
{
    if (number < 0)
        return 1;
    else
        return 0;
}

static int is_it_smol(double number)
{
    if ((int)number < 1)
        return 1;
    else
        return 0;
}

char *my_float_to_hex(double number, int precision, char caps)
{
    char *result = malloc(sizeof(char) * 16);
    int part = (int)number;
    double nb = number - part;

    result[0] = part + '0';
    result[1] = '.';
    for (int i = 0; i < 13; i++) {
        nb *= 16;
        part = (int)nb;
        if (part >= 0 && part <= 9)
            result[2 + i] = part + '0';
        if (part >= 10 && part <= 16)
            result[2 + i] = part + caps - 10;
        nb -= part;
    }
    return result;
}

char *create_the_str(double number, int precision, int is_smol, char caps)
{
    char *output = malloc(sizeof(char) * precision + 8);
    char *hex = malloc(sizeof(char) * 16);
    int i = 0;

    hex = my_float_to_hex(number, precision, caps);
    output[0] = '0';
    output[1] = caps + 23;
    for (i; hex[i] != '\0' && i < precision + 2; i++)
        output[2 + i] = hex[i];
    output[2 + i] = caps + 15;
    if (is_smol)
        output[3 + i] = '-';
    else
        output[3 + i] = '+';
    return output;
}

char *create_the_str_bis(char *output, int exponent)
{
    int size = my_strlen(output);
    int exp_size = count_digit(exponent);
    int temp = 1;

    for (int i = 0; i <= 4; i++) {
        if (exponent < 10) {
            output[size + i] = exponent + '0';
            break;
        } else {
            temp = ((exponent - (exponent % my_pow(10, exp_size - 1)))
                    / my_pow(10, exp_size - 1));
            output[size + i] = temp + '0';
        }
        exponent -= temp * my_pow(10, exp_size - 1);
        exp_size -= 1;
    }
    return output;
}

int flag_a(double number, int precision, char caps)
{
    char *output = malloc(sizeof(char) * precision + 12);
    int exponent = 0;
    int is_negative = make_it_positive(number);
    int is_smol = is_it_smol(number);

    if (is_negative) {
        number *= -1;
        my_putchar('-');
    }
    while ((int)number != 1) {
        if (is_smol)
            number *= 2;
        if (!is_smol)
            number /= 2;
        exponent++;
    }
    output = create_the_str(number, precision, is_smol, caps);
    output = create_the_str_bis(output, exponent);
    my_putstr(output);
}
