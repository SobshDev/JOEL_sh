/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** create_elif_node
*/

#include "parser.h"

node_t *create_elif_node(node_t *condition, node_t *then_branch)
{
    node_t *node = create_empty_node();

    if (!node)
        return NULL;
    node->type = NODE_ELIF;
    node->left = condition;
    node->right = then_branch;
    return node;
}
