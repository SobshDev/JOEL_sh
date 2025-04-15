/*
** EPITECH PROJECT, 2024
** day05
** File description:
** day05
*/

#include "my.h"

int my_compute_square_root(int nb)
{
    if (nb < 0)
        return 0;
    if (nb == 1)
        return 1;
    for (int i = 1; i <= nb / 2; i++) {
        if ((i * i) == nb)
            return i;
    }
    return 0;
}
