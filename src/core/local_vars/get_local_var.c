/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** get_local_var
*/

#include "minishell2.h"
#include "my.h"

char *get_local_var(shell_t *shell, char *name)
{
    env_value_t **local_vars = shell->local_vars;
    int i = 0;

    if (!shell || !name || !local_vars)
        return NULL;
    while (local_vars[i]) {
        if (my_strcmp(local_vars[i]->env, name) == 0)
            return (local_vars[i]->value);
        i++;
    }
    return NULL;
}
