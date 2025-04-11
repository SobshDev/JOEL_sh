/*
** EPITECH PROJECT, 2024
** my_isneg
** File description:
** day03 piscine
*/

#include "my.h"

int my_isneg(int n)
{
    if (n < 0)
        my_putchar('N');
    else
        my_putchar('P');
    return 0;
}
