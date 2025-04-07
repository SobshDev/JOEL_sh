/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

#include <stddef.h>
#include "my.h"

char *my_strcat(char *dest, char const *src)
{
    int i = 0;
    int len = my_strlen(dest);

    for (; src[i] != '\0'; i++)
        dest[len + i] = src[i];
    dest[len + i] = '\0';
    return dest;
}
