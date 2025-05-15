/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** parse_group
*/

#include "parser.h"

node_t *parse_group(parser_t *parser)
{
    token_t token = peek_token(parser->lexer);
    node_t *group_node;

    if (token.type == LPAREN) {
        token = next_token(parser->lexer);
        group_node = parse_sequence(parser);
        if (!group_node) {
            return NULL;
        }
        token = next_token(parser->lexer);
        if (token.type != RPAREN) {
            destroy_node(group_node);
            return NULL;
        }
        return create_group_node(group_node);
    } else
        return parse_command(parser);
}
