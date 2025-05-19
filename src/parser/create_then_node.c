/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** create_then_node
*/

#include "parser.h"

node_t *create_then_node(node_t *commands)
{
    node_t *node = create_empty_node();

    if (!node)
        return NULL;
    node->type = NODE_THEN;
    node->left = commands;
    return node;
}
