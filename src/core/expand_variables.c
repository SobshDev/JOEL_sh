/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** expand_variables
*/

#include "minishell2.h"
#include "utils.h"
#include "my.h"

static void try_to_replace(char **arg, char *var_name, char *replacement)
{
    char *expanded = NULL;

    expanded = my_str_replace(*arg, var_name, replacement);
    if (expanded) {
        free(*arg);
        *arg = expanded;
    }
    free(replacement);
}

static void build_var_ref(char *dest, const char *name)
{
    dest[0] = '$';
    my_strcpy(&dest[1], name);
}

static int extract_env_name(char *dest, const char *env_string)
{
    int i = 0;

    while (env_string[i] && env_string[i] != '=')
        i++;
    if (env_string[i] != '=')
        return 0;
    my_strncpy(dest, env_string, i);
    dest[i] = '\0';
    return i;
}

static void expand_special_variables(shell_t *shell, node_t *node, int index)
{
    try_to_replace(&node->args[index], "$?", my_itoa(shell->exit_value));
    try_to_replace(&node->args[index], "$$", my_itoa(getpid()));
    try_to_replace(&node->args[index], "$!", my_itoa(shell->job_count));
    if (shell->special_vars->term)
        try_to_replace(&node->args[index], "$TERM",
            my_strdup(shell->special_vars->term));
    if (shell->special_vars->cwd)
        try_to_replace(&node->args[index], "$cwd",
            my_strdup(shell->special_vars->cwd));
    if (shell->special_vars->cwdcmd)
        try_to_replace(&node->args[index], "$cwdcmd",
            my_strdup(shell->special_vars->cwdcmd));
    if (shell->special_vars->precmd)
        try_to_replace(&node->args[index], "$precmd",
            my_strdup(shell->special_vars->precmd));
    if (shell->special_vars->ignoreeof)
        try_to_replace(&node->args[index], "$ignoreeof",
            my_itoa(shell->special_vars->ignoreeof));
}

static void expand_env_vars(shell_t *shell, node_t *node, int index)
{
    char var_name[256];
    char var_ref[256];
    char *value;

    if (!shell || !shell->env)
        return;
    for (int i = 0; shell->env[i]; i++) {
        if (!extract_env_name(var_name, shell->env[i]))
            continue;
        build_var_ref(var_ref, var_name);
        value = my_getenv(shell->env, var_name);
        if (value)
            try_to_replace(&node->args[index], var_ref, my_strdup(value));
    }
}

static void expand_local_vars(shell_t *shell, node_t *node, int index)
{
    char var_ref[256];

    for (int i = 0; shell->local_vars && shell->local_vars[i]; i++) {
        var_ref[0] = '$';
        my_strcpy(&var_ref[1], shell->local_vars[i]->env);
        try_to_replace(&node->args[index], var_ref,
            my_strdup(shell->local_vars[i]->value));
    }
}

void expand_variables(shell_t *shell, node_t *node)
{
    for (int i = 0; node->args[i] != NULL; i++) {
        if (node->quoted_args && node->quoted_args[i])
            continue;
        expand_special_variables(shell, node, i);
        expand_env_vars(shell, node, i);
        expand_local_vars(shell, node, i);
    }
}
