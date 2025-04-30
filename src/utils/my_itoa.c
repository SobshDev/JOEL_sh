/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** my_itoa
*/

#include "utils.h"
#include "my.h"

char *my_itoa(int value)
{
    int len = 0;
    int temp = value;
    char *str;

    if (value == 0)
        return my_strdup("0");
    while (temp != 0) {
        temp /= 10;
        len += 1;
    }
    str = malloc(sizeof(char) * (len + 1));
    if (str == NULL)
        return NULL;
    str[len] = '\0';
    while (value != 0) {
        len--;
        str[len] = (value % 10) + '0';
        value /= 10;
    }
    return str;
}
