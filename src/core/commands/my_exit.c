/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_exit.c
*/

#include "minishell2.h"
#include "my.h"

static void get_exit_code(shell_t *shell, node_t *node)
{
    if (node->args[1] != NULL && my_str_isnum(node->args[1]) == 0) {
        my_putstr_err("exit: Expression Syntax.\n");
        shell->exit_value = 1;
    } else if (node->args[1] != NULL) {
        shell->exit_value = my_getnbr(node->args[1]);
    } else {
        return;
    }
}

void my_exit(shell_t *shell, node_t *node)
{
    size_t exitval = 0;

    get_exit_code(shell, node);
    exitval = shell->exit_value;
    if (node->args[1] != NULL && my_str_isnum(node->args[1])) {
        exitval = my_getnbr(node->args[1]);
    }
    if (shell->in_group_context || shell->in_logic_context) {
        shell->exit_value = exitval;
        return;
    }
    my_putstr("exit\n");
    free_shell(shell);
    exit(exitval);
}
