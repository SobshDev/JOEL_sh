/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** create_condition_node
*/

#include "parser.h"

node_t *create_condition_node(node_t *expression)
{
    node_t *node = create_empty_node();

    if (!node)
        return NULL;
    node->type = NODE_CONDITION;
    node->left = expression;
    return node;
}
