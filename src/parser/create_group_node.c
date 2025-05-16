/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** create_group_node
*/

#include "parser.h"

node_t *create_group_node(node_t *left)
{
    node_t *node = create_empty_node();

    if (!node)
        return NULL;
    node->type = NODE_GROUP;
    node->left = left;
    return node;
}
