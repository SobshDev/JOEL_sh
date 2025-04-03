/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

#include "my.h"

void my_putstr_err(char const *str)
{
    write(2, str, my_strlen(str));
}
