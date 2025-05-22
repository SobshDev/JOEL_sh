/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** handle_cmd_line
*/

#include "minishell2.h"
#include "my.h"

static void handle_errors(shell_t *shell, parser_t *parser)
{
    if (parser->syntax_error) {
        destroy_parser(parser);
        free_shell(shell);
        exit(1);
    }
    if (!parser->root) {
        destroy_parser(parser);
        free_shell(shell);
        exit(84);
    }
}

void handle_cmd_line(shell_t *shell)
{
    parser_t *parser = NULL;

    expand_history(shell);
    if (shell->history_expansion_failed) {
        shell->history_expansion_failed = false;
        return;
    }
    add_history_entry(shell->history, shell->input);
    parser = create_parser(my_strdup(shell->input));
    if (!parser) {
        free_shell(shell);
        exit(84);
    }
    parser->root = parse(parser);
    handle_errors(shell, parser);
    execute_ast(shell, parser->root);
    destroy_parser(parser);
}
