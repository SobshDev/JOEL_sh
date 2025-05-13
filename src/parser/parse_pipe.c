/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** parse_pipe
*/

#include "parser.h"

static node_t *get_pipe_node(node_t *left, node_t *right)
{
    node_t *node = create_pipe_node(left, right);

    if (!node) {
        destroy_node(left);
        destroy_node(right);
        return NULL;
    }
    return node;
}

/*
 * Parses a pipe sequence in the shell command line.
 * The function first parses a command, then checks for the pipe operator.
 * If found, it continues parsing the next command in the sequence.
 */
node_t *parse_pipe(parser_t *parser)
{
    node_t *node = parse_redirect(parser, NULL);
    node_t *right = NULL;
    node_t *pipe_node = NULL;

    if (!node)
        return NULL;
    while (peek_token(parser->lexer).type == PIPE) {
        next_token(parser->lexer);
        right = parse_redirect(parser, NULL);
        if (!right) {
            destroy_node(node);
            return NULL;
        }
        pipe_node = get_pipe_node(node, right);
        if (!pipe_node)
            return NULL;
        node = pipe_node;
    }
    return node;
}
