/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** file_exists
*/

#include "utils.h"
#include "my.h"

bool file_exists(char *path)
{
    if (access(path, F_OK) != 0) {
        my_putstr_err(path);
        my_putstr_err(": No such file or directory.\n");
        return false;
    }
    return true;
}
