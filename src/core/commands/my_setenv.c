/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_setenv
*/

#include "minishell2.h"
#include "my.h"

bool is_valid_first_char(char *str)
{
    if (str[0] >= 'A' && str[0] <= 'Z')
        return true;
    if (str[0] >= 'a' && str[0] <= 'z')
        return true;
    if (str[0] == '_')
        return true;
    return false;
}

bool is_valid_env_name(char *str)
{
    for (int i = 1; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            continue;
        if (str[i] >= 'a' && str[i] <= 'z')
            continue;
        if (str[i] >= '0' && str[i] <= '9')
            continue;
        if (str[i] == '_')
            continue;
        return false;
    }
    return true;
}

void my_setenv(shell_t *shell, node_t *node)
{
    int len = my_arraylen(node->args);

    if (len > 3) {
        my_putstr_err("setenv: Too many arguments.\n");
        return;
    }
    if (len == 1)
        return my_env(shell, node);
    if (!is_valid_first_char(node->args[1])) {
        my_putstr_err("setenv: Variable name must begin with a letter.\n");
        return;
    }
    if (!is_valid_env_name(node->args[1])) {
        my_putstr_err("setenv: Variable name must contain alphanumeric ");
        my_putstr_err("characters.\n");
        return;
    }
    if (my_getenv(shell->env, node->args[1]) != NULL)
        return change_env_value(shell, node->args[1], node->args[2]);
    return add_env_value(shell, node->args[1], node->args[2]);
}
