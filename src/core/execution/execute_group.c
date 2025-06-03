/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** execute_group
*/

#include "minishell2.h"

static void handle_group_context(shell_t *shell, node_t *node)
{
    bool prev_context = shell->in_group_context;

    shell->in_group_context = true;
    execute_ast(shell, node->left);
    shell->in_group_context = prev_context;
}

void execute_group(shell_t *shell, node_t *node)
{
    handle_group_context(shell, node);
    if (node->left) {
        execute_ast(shell, node->left);
    }
}
