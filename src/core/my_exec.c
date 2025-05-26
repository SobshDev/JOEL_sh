/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_exec.c
*/

#include "minishell2.h"
#include "utils.h"
#include "my.h"
#include "font.h"

char *free_paths(char **paths, char *path)
{
    if (paths != NULL) {
        for (int i = 0; paths[i] != NULL; i++)
            free(paths[i]);
        free(paths);
    }
    return path;
}

static char *try_path(char *base_path, char *cmd)
{
    int path_len = my_strlen(base_path);
    int cmd_len = my_strlen(cmd);
    char *full_path = malloc(path_len + 1 + cmd_len + 1);

    if (full_path == NULL)
        return NULL;
    my_strcpy(full_path, base_path);
    my_strcat(full_path, "/");
    my_strcat(full_path, cmd);
    return full_path;
}

char *get_path(shell_t *shell, node_t *node)
{
    char **paths = NULL;
    char *path = NULL;
    char *env_path = NULL;

    if (access(node->args[0], X_OK) == 0)
        return my_strdup(node->args[0]);
    env_path = my_getenv(shell->env, "PATH");
    if (env_path == NULL)
        return my_strdup(node->args[0]);
    paths = my_str_to_word_array(env_path, ":");
    if (paths == NULL)
        return my_strdup(node->args[0]);
    for (int i = 0; paths[i] != NULL; i++) {
        path = try_path(paths[i], node->args[0]);
        if (path != NULL && access(path, X_OK) == 0)
            break;
        free(path);
        path = NULL;
    }
    return free_paths(paths, path);
}

static void handle_signal_output(int signal)
{
    switch (signal) {
        case 8:
            my_putstr_err("Floating exception");
            break;
        case 11:
            my_putstr_err("Segmentation fault");
            break;
        default:
            break;
    }
}

static void handle_parent(shell_t *shell, int status)
{
    if (WIFSIGNALED(status)) {
        handle_signal_output(WTERMSIG(status));
        if (__WCOREDUMP(status))
            my_putstr_err(" (core dumped)");
        my_putstr_err("\n");
        shell->exit_value = WTERMSIG(status) + 128;
    } else if (WIFEXITED(status))
        shell->exit_value = WEXITSTATUS(status);
}

static void bad_path(shell_t *shell, node_t *node)
{
    if (access(node->args[0], F_OK) == 0) {
        if (access(node->args[0], X_OK) != 0) {
            my_putstr_err(node->args[0]);
            my_putstr_err(": Permission denied.\n");
        }
        shell->exit_value = 1;
        my_exit(shell, node);
    } else {
        my_putstr_err(node->args[0]);
        my_putstr_err(": Command not found.\n");
        shell->exit_value = 1;
    }
}

static void child_process(char *path, node_t *node, shell_t *shell)
{
    execve(path, node->args, shell->env);
    if (errno == ENOEXEC) {
        my_putstr_err(path);
        my_putstr_err(": Exec format error. Binary file not executable.\n");
    } else if (errno == EACCES) {
        my_putstr_err(path);
        my_putstr_err(": Permission denied.\n");
    } else
        my_perror(path);
    exit(1);
}

void my_exec(shell_t *shell, node_t *node)
{
    pid_t pid;
    char *path = NULL;
    int status = 0;

    if (node->args[0] == NULL || node->args[0][0] == '\0')
        return;
    path = get_path(shell, node);
    if (path == NULL)
        return bad_path(shell, node);
    pid = fork();
    switch (pid) {
        case -1:
            return perror("fork");
        case 0:
            return child_process(path, node, shell);
        default:
            waitpid(pid, &status, 0);
            free(path);
            return handle_parent(shell, status);
    }
}
