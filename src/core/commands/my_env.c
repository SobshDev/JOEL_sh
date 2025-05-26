/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_env.c
*/

#include "minishell2.h"
#include "my.h"

void my_env(shell_t *shell, node_t *node)
{
    for (int i = 0; shell->env[i] != NULL; i++) {
        my_putstr(shell->env[i]);
        my_putstr("\n");
    }
    (void)node;
}
