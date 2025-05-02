/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** my_strndup
*/

#include "utils.h"

char *my_strndup(char const *src, int n)
{
    char *dest = malloc(sizeof(char) * (n + 1));
    int i = 0;

    if (!dest)
        return NULL;
    while (src[i] && i < n) {
        dest[i] = src[i];
        i += 1;
    }
    dest[i] = '\0';
    return dest;
}
