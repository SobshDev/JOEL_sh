/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** create_redirect_node
*/

#include "parser.h"

node_t *create_redirect_node(node_t *left, node_t *right, token_type_t type,
    char *path)
{
    node_t *node = create_empty_node();

    if (!node)
        return NULL;
    node->type = NODE_REDIRECT;
    node->left = left;
    node->right = right;
    node->redirect_type = type;
    node->redirect_path = path;
    return node;
}
