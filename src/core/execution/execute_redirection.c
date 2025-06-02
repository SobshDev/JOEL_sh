/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** execute_redirection
*/

#include "minishell2.h"
#include "my.h"
#include "utils.h"

static int open_with_redir_in(shell_t *shell, node_t *node)
{
    if (!file_exists(node->redirect_path) ||
        is_directory(node->redirect_path)) {
        shell->exit_value = 1;
        return -1;
    }
    return open(node->redirect_path, O_RDONLY);
}

static int open_with_redir_out(shell_t *shell, node_t *node)
{
    if (is_directory(node->redirect_path)) {
        shell->exit_value = 1;
        return -1;
    }
    return open(node->redirect_path, O_WRONLY | O_CREAT | O_TRUNC, 0664);
}

static int open_with_redir_append(shell_t *shell, node_t *node)
{
    if (is_directory(node->redirect_path)) {
        shell->exit_value = 1;
        return -1;
    }
    return open(node->redirect_path, O_WRONLY | O_CREAT | O_APPEND, 0664);
}

static int open_with_redir_error(shell_t *shell, node_t *node)
{
    if (is_directory(node->redirect_path)) {
        shell->exit_value = 1;
        return -1;
    }
    return open(node->redirect_path, O_WRONLY | O_CREAT | O_TRUNC, 0664);
}

static int open_with_redir_both(shell_t *shell, node_t *node)
{
    if (is_directory(node->redirect_path)) {
        shell->exit_value = 1;
        return -1;
    }
    return open(node->redirect_path, O_WRONLY | O_CREAT | O_TRUNC, 0664);
}

static int open_with_redir_type(shell_t *shell, node_t *node)
{
    switch (node->redirect_type) {
        case REDIRECT_IN:
            return open_with_redir_in(shell, node);
        case REDIRECT_OUT:
            return open_with_redir_out(shell, node);
        case REDIRECT_APPEND:
            return open_with_redir_append(shell, node);
        case REDIRECT_ERROR:
            return open_with_redir_error(shell, node);
        case REDIRECT_BOTH:
            return open_with_redir_both(shell, node);
        case UNKNOWN:
            my_putstr_err("Missing name for redirect.\n");
            return -1;
        default:
            return -1;
    }
}

static void redir_logic(node_t *node, int fd)
{
    switch (node->redirect_type) {
        case REDIRECT_IN:
            dup2(fd, STDIN_FILENO);
            break;
        case REDIRECT_OUT:
        case REDIRECT_APPEND:
            dup2(fd, STDOUT_FILENO);
            break;
        case REDIRECT_ERROR:
            dup2(fd, STDERR_FILENO);
            break;
        case REDIRECT_BOTH:
            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
            break;
        default:
            return;
    }
    close(fd);
}

static bool catch_errors(shell_t *shell, node_t *node, int *fd)
{
    if (node->left->type == NODE_GROUP) {
        *fd = open_with_redir_type(shell, node);
        if (*fd < 0) {
            shell->exit_value = 1;
            return true;
        }
        return false;
    }
    if (!node->left->args || !node->left->args[0]) {
        shell->exit_value = 1;
        my_putstr_err("Invalid null command.\n");
        return true;
    }
    *fd = open_with_redir_type(shell, node);
    if (*fd < 0) {
        shell->exit_value = 1;
        return true;
    }
    return false;
}

/*
* Executes a command with redirection
*
* This is done by using dup2 to redirect the input/output
* to the file specified in the redirection node
*/
void execute_redirection(shell_t *shell, node_t *node)
{
    pid_t pid;
    int status;
    int fd = 0;

    if (catch_errors(shell, node, &fd))
        return;
    pid = fork();
    if (pid < 0)
        return perror("Failed to fork");
    if (pid == 0) {
        redir_logic(node, fd);
        execute_ast(shell, node->left);
        exit(shell->exit_value);
    }
    close(fd);
    waitpid(pid, &status, 0);
    shell->exit_value = WEXITSTATUS(status);
}
