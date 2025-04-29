/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** getenv
*/

#include "minishell2.h"
#include "my.h"

char *my_getenv(char **env, char *name)
{
    int name_len = my_strlen(name);

    for (int i = 0; env[i] != NULL; i++) {
        if (my_strncmp(env[i], name, name_len) == 0 &&
            env[i][name_len] == '=') {
            return env[i] + name_len + 1;
        }
    }
    return NULL;
}
