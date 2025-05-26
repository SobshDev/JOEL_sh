/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** evaluate_condition
*/

#include "minishell2.h"

bool evaluate_condition(shell_t *shell, node_t *condition)
{
    int exit_status;
    int prev_exit_status = shell->exit_value;

    if (!condition || !condition->left || condition->type != NODE_CONDITION)
        return false;
    execute_ast(shell, condition->left);
    exit_status = shell->exit_value;
    shell->exit_value = prev_exit_status;
    return exit_status == 0;
}
