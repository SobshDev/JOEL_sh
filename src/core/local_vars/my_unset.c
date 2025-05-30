/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** unset_builtin
*/

#include "minishell2.h"
#include "my.h"

/*
* Built-in 'unset' command
* Removes local variables by name
* Usage: unset variable1 [variable2 ...]
*/
void my_unset(shell_t *shell, node_t *node)
{
    int i = 1;

    while (node->args[i] != NULL) {
        unset_local_var(shell, node->args[i]);
        i++;
    }
    shell->exit_value = 0;
}
