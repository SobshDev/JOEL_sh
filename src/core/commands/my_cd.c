/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_cd.c
*/

#include "minishell2.h"
#include "my.h"

static void handle_cd_dash(shell_t *shell)
{
    char *env = my_getenv(shell->env, "OLDPWD");

    if (env != NULL) {
        chdir(env);
    } else {
        my_putstr_err(": No such file or directory.\n");
    }
}

static void handle_cd_tilde(shell_t *shell)
{
    char *env = my_getenv(shell->env, "HOME");

    if (env != NULL) {
        chdir(env);
    } else {
        my_putstr_err("HOME environment variable not set.\n");
    }
}

static void handle_cd_path(shell_t *shell, node_t *node)
{
    struct stat path_stat;

    if (access(node->args[1], F_OK) == -1) {
        my_putstr_err(node->args[1]);
        my_putstr_err(": No such file or directory.\n");
        shell->exit_value = 1;
        return;
    } else {
        stat(node->args[1], &path_stat);
        if (!S_ISDIR(path_stat.st_mode)) {
            my_putstr_err(node->args[1]);
            my_putstr_err(": Not a directory.\n");
            shell->exit_value = 1;
            return;
        }
        chdir(node->args[1]);
    }
}

void handle_cd(shell_t *shell, node_t *node)
{
    if (my_strncmp(node->args[1], "-", 2) == 0) {
        handle_cd_dash(shell);
    } else if (my_strncmp(node->args[1], "~", 2) == 0) {
        handle_cd_tilde(shell);
    } else {
        handle_cd_path(shell, node);
    }
}

void my_cd(shell_t *shell, node_t *node)
{
    char *env = NULL;
    char cwd[1024];

    if (my_getenv(shell->env, "OLDPWD") == NULL)
        add_env_value(shell, "OLDPWD", my_getenv(shell->env, "PWD"));
    if (node->args[1] != NULL) {
        handle_cd(shell, node);
    } else {
        env = my_getenv(shell->env, "HOME");
        if (env == NULL) {
            my_putstr_err("HOME environment variable not set.\n");
            return;
        }
        chdir(env);
    }
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        change_env_value(shell, "OLDPWD", my_getenv(shell->env, "PWD"));
        change_env_value(shell, "PWD", cwd);
    }
    update_cwd(shell);
}
