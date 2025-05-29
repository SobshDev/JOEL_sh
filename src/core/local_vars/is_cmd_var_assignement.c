/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** is_cmd_var_assignement
*/

#include "minishell2.h"
#include "utils.h"

bool is_cmd_var_assignement(node_t *cmd_node)
{
    if (!cmd_node || !cmd_node->args || cmd_node->arg_count != 3)
        return false;
    if (strcmp(cmd_node->args[1], "=") != 0)
        return false;
    if (cmd_node->args[0] == NULL || cmd_node->args[1] == NULL)
        return false;
    if (!is_valid_var_name(cmd_node->args[0]))
        return false;
    return true;
}
