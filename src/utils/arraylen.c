/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** arraylen
*/

#include <stddef.h>

int my_arraylen(char **array)
{
    int len = 0;

    while (array != NULL && array[len] != NULL)
        len++;
    return len;
}
