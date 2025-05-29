/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** remove_local_var
*/

#include "minishell2.h"
#include "my.h"

static void shift_array_elements(env_value_t **array, int pos)
{
    int i = pos;

    if (!array)
        return;
    while (array[i + 1] != NULL) {
        array[i] = array[i + 1];
        i++;
    }
    array[i] = NULL;
}

void unset_local_var(shell_t *shell, char *name)
{
    int i = 0;

    if (!shell || !name || !shell->local_vars)
        return;
    while (shell->local_vars[i]) {
        if (my_strcmp(shell->local_vars[i]->env, name) == 0) {
            free(shell->local_vars[i]->env);
            free(shell->local_vars[i]->value);
            free(shell->local_vars[i]);
            shift_array_elements(shell->local_vars, i);
            return;
        }
        i++;
    }
}
