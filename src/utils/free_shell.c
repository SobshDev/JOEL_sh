/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** free_shell.c
*/

#include "minishell2.h"

static void free_env_value(env_value_t *env_value)
{
    if (env_value) {
        free(env_value->env);
        free(env_value->value);
        free(env_value);
    }
}

static void free_special_vars(special_vars_t *special_vars)
{
    if (special_vars) {
        if (special_vars->term)
            free(special_vars->term);
        if (special_vars->cwd)
            free(special_vars->cwd);
        if (special_vars->precmd)
            free(special_vars->precmd);
        if (special_vars->cwdcmd)
            free(special_vars->cwdcmd);
        free(special_vars);
    }
}

void free_shell(shell_t *shell)
{
    int env_len = my_arraylen(shell->env);

    if (shell->input)
        free(shell->input);
    if (shell->env) {
        for (int i = 0; i < env_len; i++)
            free(shell->env[i]);
        free(shell->env);
    }
    if (shell->history)
        destroy_history(shell->history);
    if (shell->env_private) {
        for (int i = 0; shell->env_private[i]; i++)
            free_env_value(shell->env_private[i]);
        free(shell->env_private);
    }
    free_special_vars(shell->special_vars);
    restore_terminal();
}
