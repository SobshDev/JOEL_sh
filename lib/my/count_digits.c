/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

#include "my.h"

int count_digits(int nb)
{
    if (nb / 10 == 0)
        return 1;
    return 1 + count_digits(nb / 10);
}
