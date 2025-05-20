/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parse_while
*/

#include "parser.h"

static bool consume_token_type(parser_t *parser,
    token_type_t type, char *token_name)
{
    token_t token = peek_token(parser->lexer);

    if (token.type != type) {
        parser->syntax_error = true;
        fprintf(stderr, "Syntax error: expected %s\n", token_name);
        return false;
    }
    next_token(parser->lexer);
    return true;
}

static bool handle_first_part(parser_t *parser, node_t **condition)
{
    if (!consume_token_type(parser, WHILE, "'while'"))
        return false;
    *condition = parse_condition(parser);
    if (*condition == NULL)
        return false;
    if (!consume_token_type(parser, SEMICOLON, "';'"))
        return false;
    return true;
}

static bool handle_second_part(parser_t *parser, node_t **commands)
{
    if (!consume_token_type(parser, DO, "'do'"))
        return false;
    *commands = parse_logical(parser);
    if (*commands == NULL)
        return false;
    if (!consume_token_type(parser, SEMICOLON, "';'"))
        return false;
    if (!consume_token_type(parser, DONE, "'done'"))
        return false;
    return true;
}

node_t *parse_while(parser_t *parser)
{
    node_t *condition = NULL;
    node_t *commands = NULL;

    if (!handle_first_part(parser, &condition))
        return NULL;
    if (!handle_second_part(parser, &commands))
        return NULL;
    return create_while_node(condition, commands);
}
