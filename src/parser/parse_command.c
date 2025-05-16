/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** parse_command
*/

#include "parser.h"
#include "utils.h"

static void null_terminate(node_t *node)
{
    size_t old_size = node->arg_count * sizeof(char *);
    size_t new_size = (node->arg_count + 1) * sizeof(char *);

    node->args = my_realloc(node->args, old_size, new_size);
    if (!node->args)
        return;
    node->args[node->arg_count] = NULL;
}

static bool add_arg(node_t *node, char *arg)
{
    size_t old_size = node->arg_count * sizeof(char *);

    if (!arg) {
        return false;
    }
    node->arg_count += 1;
    node->args = my_realloc(node->args, old_size, old_size + sizeof(char *));
    if (!node->args) {
        free(arg);
        return false;
    }
    node->args[node->arg_count - 1] = arg;
    return true;
}

static void flag_quoted_arg(parser_t *parser, node_t *node)
{
    size_t new_size = (node->arg_count + 1) * sizeof(bool);

    if (!node->quoted_args) {
        node->quoted_args = calloc(node->arg_count, sizeof(bool));
    } else {
        node->quoted_args = realloc(node->quoted_args, new_size);
        node->quoted_args[node->arg_count - 1] = false;
    }
    if (!node->quoted_args)
        return;
    if (peek_token(parser->lexer).is_quoted)
        node->quoted_args[node->arg_count - 1] = true;
}

static void flag_backticked_arg(parser_t *parser, node_t *node)
{
    size_t new_size = (node->arg_count + 1) * sizeof(bool);

    if (!node->backticked_args) {
        node->backticked_args = calloc(node->arg_count, sizeof(bool));
    } else {
        node->backticked_args = realloc(node->backticked_args, new_size);
        node->backticked_args[node->arg_count - 1] = false;
    }
    if (!node->backticked_args)
        return;
    if (peek_token(parser->lexer).is_backticked)
        node->backticked_args[node->arg_count - 1] = true;
}

static bool parse_arg(parser_t *parser, node_t *node)
{
    token_t token = peek_token(parser->lexer);
    char *arg = my_strndup(parser->lexer->content + token.text_start,
                token.text_len);

    if (!add_arg(node, arg)) {
        free(arg);
        destroy_node(node);
        return false;
    }
    flag_quoted_arg(parser, node);
    flag_backticked_arg(parser, node);
    next_token(parser->lexer);
    return true;
}

/*
* Parses a command in the shell command line.
* The function first checks for a command token (WORD).
* If found, it continues parsing the arguments of the command.
*/
node_t *parse_command(parser_t *parser)
{
    node_t *node;
    token_t token = peek_token(parser->lexer);

    if (token.type == IF)
        return parse_if(parser);
    if (token.type == WHILE)
        return parse_while(parser);
    node = create_empty_node();
    if (!node)
        return NULL;
    node->type = NODE_COMMAND;
    while (token.type == WORD || token.type == EQUALS) {
        if (!parse_arg(parser, node))
            return NULL;
        token = peek_token(parser->lexer);
    }
    null_terminate(node);
    return node;
}
