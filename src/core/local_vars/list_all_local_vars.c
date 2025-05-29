/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** list_all_local_vars
*/

#include "minishell2.h"
#include "my.h"

void my_vars(shell_t *shell, node_t *node)
{
    int i = 0;
    env_value_t *local_var = shell->local_vars[0];

    while (local_var != NULL) {
        if (local_var->env != NULL && local_var->value != NULL) {
            my_printf("%s=%s\n", local_var->env, local_var->value);
        }
        i += 1;
        local_var = shell->local_vars[i];
    }
    (void)node;
}
