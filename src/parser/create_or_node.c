/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** create_or_node
*/

#include "parser.h"

node_t *create_or_node(node_t *left, node_t *right)
{
    node_t *node = create_empty_node();

    if (!node)
        return NULL;
    node->type = NODE_OR;
    node->left = left;
    node->right = right;
    return node;
}
