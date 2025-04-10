/*
** EPITECH PROJECT, 2024
** day03
** File description:
** day03
*/

#include <stdio.h>
#include "my.h"


void hardcoded(void)
{
    my_putchar('2');
    my_putchar('1');
    my_putchar('4');
    my_putchar('7');
    my_putchar('4');
    my_putchar('8');
    my_putchar('3');
    my_putchar('6');
    my_putchar('4');
    my_putchar('8');
}

int my_put_nbr(int nb)
{
    int temp_nb = nb;

    if (temp_nb < 0) {
        my_putchar('-');
        temp_nb = temp_nb * (-1);
    }
    if (temp_nb == -2147483648) {
        hardcoded();
        return 0;
    }
    if (temp_nb < 10)
        my_putchar(temp_nb + '0');
    else {
        my_put_nbr(temp_nb / 10);
        my_putchar((temp_nb % 10) + '0');
    }
    return 0;
}
