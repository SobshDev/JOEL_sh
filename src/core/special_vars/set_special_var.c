/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** set_special_var
*/

#include "minishell2.h"
#include "utils.h"
#include "my.h"

void set_special_var(shell_t *shell, const char *name, const char *value)
{
    if (strcmp(name, "term") == 0) {
        free(shell->special_vars->term);
        shell->special_vars->term = my_strdup(value);
    }
    if (strcmp(name, "cwd") == 0) {
        fprintf(stderr, "Warning: cwd is read-only\n");
    }
    if (strcmp(name, "cwdcmd") == 0) {
        free(shell->special_vars->cwdcmd);
        shell->special_vars->cwdcmd = my_strdup(value);
    }
    if (strcmp(name, "precmd") == 0) {
        free(shell->special_vars->precmd);
        shell->special_vars->precmd = my_strdup(value);
    }
    if (strcmp(name, "ignoreeof") == 0) {
        shell->special_vars->ignoreeof = atoi(value);
        shell->special_vars->eofcount = 0;
    }
}
