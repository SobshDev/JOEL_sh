/*
** EPITECH PROJECT, 2024
** day05
** File description:
** day05
*/

#include "my.h"

int my_pow(int nb, int p)
{
    int cpy = nb;

    if (p == 0)
        return 1;
    if (p < 0)
        return 0;
    return nb * my_pow(cpy, p - 1);
}
