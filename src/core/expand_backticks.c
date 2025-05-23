/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** expand_backticks
*/

#include "minishell2.h"
#include "utils.h"
#include "my.h"

void expand_backticks(node_t *node)
{
    char *output = NULL;

    for (int i = 0; i < node->arg_count; ++i) {
        if (node->backticked_args && node->backticked_args[i]) {
            output = run_backtick_command(node->args[i]);
            free(node->args[i]);
            node->args[i] = output ? output : my_strdup("");
        }
    }
}
