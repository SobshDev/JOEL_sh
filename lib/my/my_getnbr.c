/*
** EPITECH PROJECT, 2024
** day04
** File description:
** day04
*/

#include <limits.h>
#include <stdio.h>

int check_negative(char const *str)
{
    int isneg = 1;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '-')
            isneg *= -1;
    }
    return isneg;
}

int check_overflow(int new_nbr)
{
    if (new_nbr < 0)
        return 0;
    return 1;
}

int my_getnbr(char const *str)
{
    int isneg = check_negative(str);
    int new_nbr = 0;
    int i = 0;
    int digit = 0;

    while (!(str[i] >= '0' && str[i] <= '9')) {
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        digit = (str[i] - '0');
        new_nbr = new_nbr * 10 + digit;
        if (new_nbr == -2147483648 && isneg == -1)
            return -2147483648;
        i++;
        if (check_overflow(new_nbr) == 0)
            return 0;
    }
    return new_nbr * isneg;
}
