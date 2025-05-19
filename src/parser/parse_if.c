/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parse_if
*/

#include "parser.h"
#include "my.h"

static bool validate_token_type(parser_t *parser, token_t token,
    token_type_t type, char *token_name)
{
    if (token.type != type) {
        parser->syntax_error = true;
        my_putstr_err("Syntax error: expected ");
        my_putstr_err(token_name);
        my_putstr_err("\n");
        return false;
    }
    return true;
}

static bool validate_condition(parser_t *parser, node_t *condition)
{
    if (!condition) {
        parser->syntax_error = true;
        my_putstr_err("Syntax error: invalid condition\n");
        return false;
    }
    return true;
}

static token_t skip_semicolon(parser_t *parser)
{
    token_t token = peek_token(parser->lexer);

    if (token.type == SEMICOLON) {
        next_token(parser->lexer);
    }
    return peek_token(parser->lexer);
}

static bool consume_token_type(parser_t *parser,
    token_type_t type, char *token_name)
{
    token_t token = peek_token(parser->lexer);

    if (!validate_token_type(parser, token, type, token_name))
        return false;
    next_token(parser->lexer);
    return true;
}

static node_t *parse_then_branch(parser_t *parser)
{
    node_t *command_sequence = NULL;

    if (!consume_token_type(parser, THEN, "'then'"))
        return NULL;
    command_sequence = parse_logical(parser);
    if (!command_sequence) {
        parser->syntax_error = true;
        my_putstr_err("Syntax error: expected command after 'then'\n");
        return NULL;
    }
    return create_then_node(command_sequence);
}

static node_t *parse_elif_branch(parser_t *parser)
{
    node_t *condition = NULL;
    node_t *commands = NULL;

    if (!consume_token_type(parser, ELIF, "'elif'"))
        return NULL;
    condition = parse_condition(parser);
    if (!validate_condition(parser, condition))
        return NULL;
    if (!consume_token_type(parser, SEMICOLON, "';'"))
        return NULL;
    commands = parse_then_branch(parser);
    if (!commands)
        return NULL;
    return create_elif_node(condition, commands);
}

static node_t *parse_else_branch(parser_t *parser)
{
    node_t *commands = NULL;

    if (!consume_token_type(parser, ELSE, "'else'"))
        return NULL;
    commands = parse_logical(parser);
    if (!commands) {
        parser->syntax_error = true;
        my_putstr_err("Syntax error: expected command after 'else'\n");
        return NULL;
    }
    return create_else_node(commands);
}

static void handle_elif(parser_t *parser, node_t **branch,
    node_t **current, token_t *token)
{
    *branch = parse_elif_branch(parser);
    if (!*branch)
        return;
    (*current)->right = *branch;
    *current = (*branch)->right;
    *token = skip_semicolon(parser);
}

node_t *handle_after_then(parser_t *parser, node_t *then_branch)
{
    token_t token = peek_token(parser->lexer);
    node_t *branch = NULL;
    node_t *current = then_branch;

    while (current->right != NULL)
        current = current->right;
    token = skip_semicolon(parser);
    while (token.type == ELIF)
        handle_elif(parser, &branch, &current, &token);
    if (token.type == ELSE) {
        branch = parse_else_branch(parser);
        if (!branch)
            return NULL;
        current->right = branch;
        token = skip_semicolon(parser);
    }
    if (!consume_token_type(parser, FI, "'fi'"))
        return NULL;
    return then_branch;
}

/*
* Parses an if statement in the format (can be on same line):
* if <condition>; then <command>;
* [elif <condition>; then <command>;] [else <command>;] fi
*/
node_t *parse_if(parser_t *parser)
{
    node_t *condition = NULL;
    node_t *then_branch = NULL;

    if (!consume_token_type(parser, IF, "'if'"))
        return NULL;
    condition = parse_condition(parser);
    if (!validate_condition(parser, condition))
        return NULL;
    if (!consume_token_type(parser, SEMICOLON, "';'"))
        return NULL;
    then_branch = parse_then_branch(parser);
    if (!then_branch)
        return NULL;
    then_branch = handle_after_then(parser, then_branch);
    if (!then_branch)
        return NULL;
    return create_if_node(condition, then_branch);
}
