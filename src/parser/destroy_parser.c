/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** destroy_parser
*/

#include "parser.h"

void destroy_node(node_t *node)
{
    if (!node)
        return;
    if (node->args) {
        for (int i = 0; i < node->arg_count; i++)
            free(node->args[i]);
        free(node->args);
    }
    if (node->quoted_args)
        free(node->quoted_args);
    if (node->backticked_args)
        free(node->backticked_args);
    if (node->redirect_path)
        free(node->redirect_path);
    destroy_node(node->left);
    destroy_node(node->right);
    free(node);
}

void destroy_parser(parser_t *parser)
{
    if (!parser)
        return;
    if (parser->lexer)
        destroy_lexer(parser->lexer);
    if (parser->root)
        destroy_node(parser->root);
    free(parser);
}
