/*
** EPITECH PROJECT, 2024
** day08
** File description:
** day08
*/

#include "my.h"

char *my_strdup(char const *src)
{
    int len = my_strlen(src);
    char *new_str = malloc(sizeof(char) * len + 1);
    int i = 0;

    for (; src[i] != '\0'; i++) {
        new_str[i] = src[i];
    }
    new_str[i] = '\0';
    return new_str;
}
