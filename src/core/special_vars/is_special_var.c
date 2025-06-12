/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** is_special_var
*/

#include "minishell2.h"
#include "utils.h"

static const char *special_vars[] = {
    "term",
    "cwd",
    "precmd",
    "cwdcmd",
    "ignoreeof",
    NULL
};

bool is_special_var(const char *name)
{
    for (int i = 0; special_vars[i]; i++) {
        if (strcmp(name, special_vars[i]) == 0)
            return true;
    }
    return false;
}
