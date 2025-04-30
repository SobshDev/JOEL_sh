/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** is_valid_var_name
*/

#include "utils.h"

bool is_valid_var_name(char *name)
{
    if (!name || !*name)
        return false;
    if (!isalpha(name[0]) && name[0] != '_')
        return false;
    for (int i = 1; name[i]; i++) {
        if (!isalnum(name[i]) && name[i] != '_')
            return false;
    }
    return true;
}
