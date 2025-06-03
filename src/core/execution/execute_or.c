/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** execute_or
*/

#include "minishell2.h"

/*
* Executes the logical OR operation between two commands
* If the first command fails, the second command is executed.
* If the first command succeeds, the second command is not executed.
*/
void execute_or(shell_t *shell, node_t *node)
{
    bool prev_logic_context = shell->in_logic_context;

    shell->in_logic_context = true;
    execute_ast(shell, node->left);
    shell->in_logic_context = prev_logic_context;
    if (shell->exit_value != 0) {
        shell->in_logic_context = true;
        execute_ast(shell, node->right);
        shell->in_logic_context = prev_logic_context;
    }
}
