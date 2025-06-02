/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** execute_command
*/

#include "minishell2.h"
#include "utils.h"
#include "my.h"

static const builtins_t builtins[] = {
    {"cd", my_cd},
    {"env", my_env},
    {"setenv", my_setenv},
    {"unsetenv", my_unsetenv},
    {"exit", my_exit},
    {"history", my_history},
    {"alias", my_alias},
    {"vars", my_vars},
    {"unset", my_unset},
    {NULL, NULL}
};

/*
* Executes a command in the shell.
* This function handles built-in commands like cd, env, setenv,
* unsetenv and exit. For other commands, it calls the my_exec function.
*/
void execute_command(shell_t *shell, node_t *node)
{
    expand_backticks(node);
    expand_globbing(node);
    expand_aliases(shell, node);
    expand_variables(shell, node);
    if (is_cmd_var_assignement(node)) {
        if (is_special_var(node->args[0]))
            return set_special_var(shell, node->args[0], node->args[2]);
        else
            return set_local_var(shell, node->args[0], node->args[2]);
    }
    if (is_cmd_var_assignement(node))
        return set_local_var(shell, node->args[0], node->args[2]);
    for (int i = 0; builtins[i].name != NULL; i++) {
        if (my_strncmp(node->args[0], builtins[i].name,
            my_strlen(builtins[i].name) + 1) == 0)
            return builtins[i].handler(shell, node);
    }
    return my_exec(shell, node);
}
