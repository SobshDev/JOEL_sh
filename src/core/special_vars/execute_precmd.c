/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** execute_precmd
*/

#include "minishell2.h"
#include "my.h"

void execute_precmd(shell_t *shell)
{
    parser_t *parser = NULL;
    char *cmd_copy = NULL;

    if (!shell->special_vars->precmd)
        return;
    cmd_copy = my_strdup(shell->special_vars->precmd);
    parser = create_parser(cmd_copy);
    if (!parser || !cmd_copy) {
        my_putstr_err("Error: Failed to execute pre-command\n");
        return;
    }
    parser->root = parse(parser);
    if (parser->root)
        execute_ast(shell, parser->root);
    destroy_parser(parser);
}
