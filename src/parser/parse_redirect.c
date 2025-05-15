/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** parse_redirect
*/

#include "parser.h"
#include "utils.h"
#include "my.h"

static bool should_parse_command(parser_t *parser)
{
    token_type_t type = peek_token(parser->lexer).type;

    if (type == END || type == PIPE || type == SEMICOLON)
        return false;
    return true;
}

static node_t *create_redirect_node_with_path(parser_t *parser,
    node_t *left, token_type_t redirect_type, char *path)
{
    node_t *right = NULL;
    node_t *node = NULL;

    if (should_parse_command(parser))
        right = parse_group(parser);
    node = create_redirect_node(left, right, redirect_type, path);
    if (!node) {
        free(path);
        destroy_node(left);
        destroy_node(right);
        return NULL;
    }
    return node;
}

static node_t *handle_path_token(parser_t *parser, node_t *left,
    token_type_t redirect_type)
{
    token_t path_token;
    char *path;

    if (peek_token(parser->lexer).type != WORD) {
        my_putstr_err("Missing name for redirect.\n");
        destroy_node(left);
        parser->syntax_error = true;
        return NULL;
    }
    path_token = next_token(parser->lexer);
    path = my_strndup(parser->lexer->content + path_token.text_start,
        path_token.text_len);
    if (!path) {
        destroy_node(left);
        return NULL;
    }
    return create_redirect_node_with_path(parser, left, redirect_type, path);
}

/*
* Parses a command with optional redirection operators.
* The function first parses a command, then checks for
* redirection operators (>, >>, <, <<). If found,
* it continues parsing the redirection path.
* The function is recursive, allowing for multiple
* redirections in a single command.
*/
node_t *parse_redirect(parser_t *parser, node_t *left)
{
    token_t token;
    token_type_t type;

    if (!left)
        left = parse_group(parser);
    if (!left)
        return NULL;
    token = peek_token(parser->lexer);
    type = token.type;
    if (is_token_redirect(type)) {
        next_token(parser->lexer);
        left = handle_path_token(parser, left, type);
        if (!left)
            return NULL;
        return parse_redirect(parser, left);
    }
    return left;
}
