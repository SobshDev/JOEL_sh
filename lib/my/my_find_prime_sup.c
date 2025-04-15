/*
** EPITECH PROJECT, 2024
** day05
** File description:
** day05
*/

#include "my.h"

int my_find_prime_sup(int nb)
{
    int is_prime = 0;

    while (is_prime != 1) {
        is_prime = my_is_prime(nb);
    if (is_prime == 1)
            return nb;
        nb += 1;
    }
    return 0;
}
