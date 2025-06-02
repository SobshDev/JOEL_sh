/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** execute_pipe
*/

#include "minishell2.h"
#include "my.h"

static bool is_builtin(node_t *node)
{
    if (!node || node->type != NODE_COMMAND || !node->args[0])
        return false;
    if (my_strncmp(node->args[0], "cd", 3) == 0 ||
            my_strncmp(node->args[0], "exit", 5) == 0 ||
            my_strncmp(node->args[0], "env", 4) == 0 ||
            my_strncmp(node->args[0], "setenv", 7) == 0 ||
            my_strncmp(node->args[0], "unsetenv", 9) == 0)
        return true;
    return false;
}

static void handle_pipe_error(shell_t *shell)
{
    my_putstr_err("Invalid null command.\n");
    shell->exit_value = 1;
}

static int handle_forking_left(shell_t *shell, int pipefd[2], node_t *node)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return 1;
    }
    if (pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execute_ast(shell, node->left);
        exit(shell->exit_value);
    }
    return pid;
}

static int handle_forking_right(shell_t *shell, int pipefd[2], node_t *node)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return 1;
    }
    if (pid == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        execute_ast(shell, node->right);
        exit(shell->exit_value);
    }
    return pid;
}

static void get_exit_value(shell_t *shell, int status_left, int status_right)
{
    if (WIFEXITED(status_right)) {
        shell->exit_value = WEXITSTATUS(status_right);
        return;
    }
    if (WIFSIGNALED(status_right)) {
        shell->exit_value = WTERMSIG(status_right) + 128;
        return;
    }
    if (shell->exit_value == 0 && WIFEXITED(status_left) &&
        WEXITSTATUS(status_left) != 0) {
        shell->exit_value = WEXITSTATUS(status_left);
        return;
    }
    if (shell->exit_value == 0 && WIFSIGNALED(status_left)) {
        shell->exit_value = WTERMSIG(status_left) + 128;
        return;
    }
}

static void handle_builtin_pipe(shell_t *shell, int pipefd[2],
    node_t *node, pid_t left_pid)
{
    int status_left;
    int saved_stdin = dup(STDIN_FILENO);

    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    execute_ast(shell, node->right);
    close(pipefd[0]);
    dup2(saved_stdin, STDIN_FILENO);
    close(saved_stdin);
    waitpid(left_pid, &status_left, 0);
}

static void handle_normal_pipe(shell_t *shell, int pipefd[2],
    node_t *node, pid_t left_pid)
{
    int status_left;
    int status_right;
    pid_t right_pid;

    right_pid = handle_forking_right(shell, pipefd, node);
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(left_pid, &status_left, 0);
    waitpid(right_pid, &status_right, 0);
    get_exit_value(shell, status_left, status_right);
}

/*
* Executes a pipe command
*
* This is done by creating a pipe and forking two processes
* The first process executes the left command and writes
* to the pipe, while the second process executes the right
* command and reads from the pipe
*
* If the right side is a builtin, we need to handle it
* differently
*/
void execute_pipe(shell_t *shell, node_t *node)
{
    int pipefd[2];
    pid_t left_pid;

    if ((node->left->type == NODE_COMMAND && !node->left->args[0]) ||
        (node->right->type == NODE_COMMAND && !node->right->args[0])) {
        handle_pipe_error(shell);
        return;
    }
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return;
    }
    left_pid = handle_forking_left(shell, pipefd, node);
    if (is_builtin(node->right))
        handle_builtin_pipe(shell, pipefd, node, left_pid);
    else
        handle_normal_pipe(shell, pipefd, node, left_pid);
}
