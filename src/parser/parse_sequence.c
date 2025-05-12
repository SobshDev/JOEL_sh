/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** parse_sequence
*/

#include "parser.h"

static node_t *get_sequence_node(node_t *left, node_t *right)
{
    node_t *node = create_sequence_node(left, right);

    if (!node) {
        destroy_node(left);
        destroy_node(right);
        return NULL;
    }
    return node;
}

/*
* Parses a sequence of commands separated by semicolons.
* The function recursively parses the left side of the sequence
* and then checks for a semicolon. If a semicolon is found,
* it continues parsing the right side of the sequence.
*/
node_t *parse_sequence(parser_t *parser)
{
    node_t *left = parse_background(parser);
    node_t *right = NULL;

    if (!left)
        return NULL;
    if (peek_token(parser->lexer).type == SEMICOLON) {
        next_token(parser->lexer);
        right = parse_sequence(parser);
        if (!right) {
            destroy_node(left);
            return NULL;
        }
        return get_sequence_node(left, right);
    }
    return left;
}
