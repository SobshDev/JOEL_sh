/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** execute_if
*/

#include "minishell2.h"

static bool handle_elif(shell_t *shell, node_t *elif_branch)
{
    node_t *condition = elif_branch->left;
    node_t *then_branch = elif_branch->right;

    if (evaluate_condition(shell, condition)) {
        execute_ast(shell, then_branch->left);
        return true;
    }
    return false;
}

static bool process_next_branch(shell_t *shell, node_t **next_branch)
{
    if ((*next_branch)->type == NODE_ELIF) {
        if (handle_elif(shell, *next_branch)) {
            return true;
        }
        *next_branch = (*next_branch)->right->right;
        return false;
    } else if ((*next_branch)->type == NODE_ELSE) {
        execute_ast(shell, (*next_branch)->left);
        return true;
    } else {
        return true;
    }
}

void execute_if(shell_t *shell, node_t *node)
{
    node_t *condition = node->left;
    node_t *then_branch = node->right;
    node_t *next_branch = NULL;
    bool done = false;

    if (evaluate_condition(shell, condition))
        return execute_ast(shell, then_branch->left);
    next_branch = then_branch->right;
    while (next_branch && !done) {
        done = process_next_branch(shell, &next_branch);
    }
}
