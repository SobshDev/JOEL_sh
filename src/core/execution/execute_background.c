/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** execute_background
*/

#include "minishell2.h"
#include "my.h"

/*
* Executes a command in the background
*
* This is done by just not waiting for the child process to finish
*/
void execute_background(shell_t *shell, node_t *node)
{
    pid_t pid = fork();

    if (pid == -1) {
        shell->exit_value = 1;
        return;
    }
    if (pid == 0) {
        execute_ast(shell, node->left);
        exit(shell->exit_value);
    } else {
        shell->job_count += 1;
        my_printf("[%d] %d\n", shell->job_count, pid);
        shell->exit_value = 0;
    }
}
