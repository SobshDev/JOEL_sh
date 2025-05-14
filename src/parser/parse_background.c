/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** parse_background
*/

#include "parser.h"

static node_t *parse_after_background(parser_t *parser, node_t *bg_node)
{
    token_t token = peek_token(parser->lexer);
    node_t *right;
    node_t *seq_node;

    if (token.type == END || token.type == SEMICOLON)
        return bg_node;
    right = parse_sequence(parser);
    if (!right) {
        destroy_node(bg_node);
        return NULL;
    }
    seq_node = create_sequence_node(bg_node, right);
    if (!seq_node) {
        destroy_node(bg_node);
        destroy_node(right);
        return NULL;
    }
    return seq_node;
}

/*
* Parses a command followed by a background operator (&).
* The function first parses the left side of the command,
* then checks for the background operator. If found,
* it creates a background node and continues parsing
*/
node_t *parse_background(parser_t *parser)
{
    node_t *left = parse_logical(parser);
    token_t token;
    node_t *bg_node;

    if (!left)
        return NULL;
    token = peek_token(parser->lexer);
    if (token.type == BACKGROUND) {
        next_token(parser->lexer);
        bg_node = create_background_node(left);
        if (!bg_node)
            return NULL;
        return parse_after_background(parser, bg_node);
    }
    return left;
}
