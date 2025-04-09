/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

#include "my.h"

void char_swap(char *a, char *b)
{
    char c = *a;

    *a = *b;
    *b = c;
}

char *my_revstr(char *str)
{
    int length = my_strlen(str);

    for (int i = 0; i != (length / 2); i++) {
        char_swap(&str[i], &str[length - i - 1]);
    }
    return str;
}
