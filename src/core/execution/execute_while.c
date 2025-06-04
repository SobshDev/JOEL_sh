/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** execute_while
*/

#include "minishell2.h"

void execute_while(shell_t *shell, node_t *node)
{
    node_t *condition = node->left;
    node_t *do_branch = node->right;

    if (condition == NULL || do_branch == NULL)
        return;
    while (evaluate_condition(shell, condition)) {
        execute_ast(shell, do_branch->left);
    }
}
