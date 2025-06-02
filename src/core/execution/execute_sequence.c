/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** execute_sequence
*/

#include "minishell2.h"

void execute_sequence(shell_t *shell, node_t *node)
{
    if (node->left) {
        execute_ast(shell, node->left);
    }
    if (node->right) {
        execute_ast(shell, node->right);
    }
}
