/*
** EPITECH PROJECT, 2024
** my_putchar
** File description:
** displays a chracter given as parameter
*/

#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}
