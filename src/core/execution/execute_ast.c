/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** traverse_ast
*/

#include "minishell2.h"

static const node_handler_t node_handlers[] = {
    [NODE_SEQUENCE] = execute_sequence,
    [NODE_PIPE] = execute_pipe,
    [NODE_REDIRECT] = execute_redirection,
    [NODE_COMMAND] = execute_command,
    [NODE_AND] = execute_and,
    [NODE_OR] = execute_or,
    [NODE_BACKGROUND] = execute_background,
    [NODE_GROUP] = execute_group,
    [NODE_IF] = execute_if,
    [NODE_WHILE] = execute_while,
    [NODE_UNKNOWN] = NULL,
};

/*
* Executes the abstract syntax tree (AST) of a command
* This is the entry point for executing the AST
*/
void execute_ast(shell_t *shell, node_t *node)
{
    if (!node)
        return;
    if (node->type >= 0 && node->type < NODE_UNKNOWN) {
        node_handlers[node->type](shell, node);
        return;
    }
    free_shell(shell);
    exit(84);
}
