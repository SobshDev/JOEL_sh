/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** change_env_value.c
*/

#include "minishell2.h"
#include "my.h"

static char *create_env_entry(const char *name, const char *value)
{
    int name_len = my_strlen(name);
    int value_len = (value != NULL) ? my_strlen(value) : 0;
    char *new_entry = malloc(name_len + 1 + value_len + 1);

    if (new_entry == NULL)
        return NULL;
    my_strcpy(new_entry, name);
    my_strcat(new_entry, "=");
    if (value != NULL)
        my_strcat(new_entry, value);
    return new_entry;
}

void change_env_value(shell_t *shell, char *name, char *value)
{
    int name_len = my_strlen(name);
    char *new_value;

    for (int i = 0; shell->env[i] != NULL; i++) {
        if (my_strncmp(shell->env[i], name, name_len) != 0 ||
            shell->env[i][name_len] != '=')
            continue;
        new_value = create_env_entry(name, value);
        if (new_value == NULL)
            return;
        free(shell->env[i]);
        shell->env[i] = new_value;
        return;
    }
}
