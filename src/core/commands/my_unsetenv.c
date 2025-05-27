/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_unsetenv.c
*/

#include "minishell2.h"
#include "my.h"

void remove_env_value(shell_t *shell, char *name)
{
    int j = 0;

    for (int i = 0; shell->env[i] != NULL; i++) {
        if (my_strncmp(shell->env[i], name, my_strlen(name)) != 0)
            continue;
        free(shell->env[i]);
        for (j = i; shell->env[j] != NULL; j++)
            shell->env[j] = shell->env[j + 1];
        shell->env[j] = NULL;
        return;
    }
}

void my_unsetenv(shell_t *shell, node_t *node)
{
    if (node->args[1] == NULL) {
        my_putstr_err("unsetenv: Too few arguments.\n");
        return;
    }
    for (int i = 1; node->args[i] != NULL; i++) {
        if (my_getenv(shell->env, node->args[i]) != NULL)
            remove_env_value(shell, node->args[i]);
    }
}
