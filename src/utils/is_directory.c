/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** is_directory
*/

#include "utils.h"
#include "my.h"

bool is_directory(char *path)
{
    struct stat sb;

    if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
        my_putstr_err(path);
        my_putstr_err(": Is a directory.\n");
        return true;
    }
    return false;
}
