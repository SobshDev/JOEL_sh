/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** parse_logical
*/

#include "parser.h"

static node_t *handle_parse_left(token_t token, node_t *left, node_t *right)
{
    if (token.type == AND)
        left = create_and_node(left, right);
    else
        left = create_or_node(left, right);
    return left;
}

/*
* Parses a logical expression (AND, OR) in the shell command line.
* The function first parses the left side of the expression,
* then checks for the logical operator (AND, OR). If found,
* it continues parsing the right side of the expression.
*/
node_t *parse_logical(parser_t *parser)
{
    node_t *left = parse_pipe(parser);
    node_t *right = NULL;
    token_t token;

    if (!left)
        return NULL;
    token = peek_token(parser->lexer);
    while (token.type == AND || token.type == OR) {
        next_token(parser->lexer);
        right = parse_pipe(parser);
        if (!right) {
            destroy_node(left);
            return NULL;
        }
        left = handle_parse_left(token, left, right);
        if (!left)
            return NULL;
        token = peek_token(parser->lexer);
    }
    return left;
}
