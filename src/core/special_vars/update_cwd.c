/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** update_cwd
*/

#include "minishell2.h"
#include "my.h"

void update_cwd(shell_t *shell)
{
    parser_t *parser = NULL;
    char *cmd_copy = NULL;

    if (shell->special_vars->cwd != NULL) {
        free(shell->special_vars->cwd);
    }
    shell->special_vars->cwd = getcwd(NULL, 0);
    if (shell->special_vars->cwdcmd && shell->special_vars->cwdcmd[0]) {
        cmd_copy = my_strdup(shell->special_vars->cwdcmd);
        parser = create_parser(cmd_copy);
        if (parser == NULL) {
            my_putstr_err("Error: Failed to create parser.\n");
            return;
        }
        parser->root = parse(parser);
        if (parser->root)
            execute_ast(shell, parser->root);
        destroy_parser(parser);
    }
}
