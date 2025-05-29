/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** set_local_vars
*/

#include "minishell2.h"
#include "my.h"

static void change_local_var_value(env_value_t **local_vars,
    char *name, char *value)
{
    int i = 0;

    if (!local_vars || !name || !value)
        return;
    while (local_vars[i]) {
        if (my_strcmp(local_vars[i]->env, name) == 0) {
            free(local_vars[i]->value);
            local_vars[i]->value = my_strdup(value);
            return;
        }
        i++;
    }
}

static void add_new_local_var(env_value_t **local_vars,
    char *name, char *value)
{
    int i = 0;

    if (!local_vars || !name || !value)
        return;
    while (local_vars[i]) {
        i++;
    }
    local_vars[i] = malloc(sizeof(env_value_t));
    if (!local_vars[i])
        return;
    local_vars[i]->env = my_strdup(name);
    local_vars[i]->value = my_strdup(value);
    local_vars[i + 1] = NULL;
}

void set_local_var(shell_t *shell, char *name, char *value)
{
    if (!shell || !name || !value)
        return;
    if (get_local_var(shell, name) != NULL) {
        change_local_var_value(shell->local_vars, name, value);
    } else {
        add_new_local_var(shell->local_vars, name, value);
    }
}
