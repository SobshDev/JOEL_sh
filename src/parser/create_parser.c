/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** create_parser
*/

#include "parser.h"

node_t *create_empty_node(void)
{
    node_t *node = malloc(sizeof(node_t));

    if (!node)
        return NULL;
    node->type = NODE_UNKNOWN;
    node->args = NULL;
    node->quoted_args = NULL;
    node->backticked_args = NULL;
    node->arg_count = 0;
    node->left = NULL;
    node->right = NULL;
    node->redirect_type = UNKNOWN;
    node->redirect_path = NULL;
    return node;
}

parser_t *create_parser(char *content)
{
    parser_t *parser = malloc(sizeof(parser_t));

    if (!parser)
        return NULL;
    parser->lexer = create_lexer(content);
    if (!parser->lexer) {
        free(parser);
        return NULL;
    }
    parser->root = NULL;
    parser->syntax_error = false;
    return parser;
}
