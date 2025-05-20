/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** create_else_node
*/

#include "parser.h"

node_t *create_else_node(node_t *commands)
{
    node_t *node = create_empty_node();

    if (!node)
        return NULL;
    node->type = NODE_ELSE;
    node->left = commands;
    return node;
}
