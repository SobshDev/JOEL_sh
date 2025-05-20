/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** create_while_node
*/

#include "parser.h"

node_t *create_while_node(node_t *condition, node_t *do_branch)
{
    node_t *node = create_empty_node();

    if (!node)
        return NULL;
    node->type = NODE_WHILE;
    node->left = condition;
    node->right = do_branch;
    return node;
}
