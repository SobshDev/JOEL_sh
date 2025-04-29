/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** add_env_value.c
*/
#include "minishell2.h"
#include "my.h"

static char *create_env_entry(char *name, char *value)
{
    int name_len = my_strlen(name);
    int value_len = (value != NULL) ? my_strlen(value) : 0;
    char *env_entry = malloc(name_len + 1 + value_len + 1);

    if (env_entry == NULL)
        return NULL;
    my_strcpy(env_entry, name);
    my_strcat(env_entry, "=");
    if (value != NULL)
        my_strcat(env_entry, value);
    return env_entry;
}

static void free_old_env(char **env)
{
    for (int i = 0; env[i] != NULL; i++)
        free(env[i]);
    free(env);
}

void add_env_value(shell_t *shell, char *name, char *value)
{
    int env_len = my_arraylen(shell->env);
    char **new_env = malloc(sizeof(char *) * (env_len + 2));
    char *env_entry;

    if (new_env == NULL)
        return;
    for (int i = 0; shell->env[i] != NULL; i++)
        new_env[i] = my_strdup(shell->env[i]);
    env_entry = create_env_entry(name, value);
    if (env_entry == NULL) {
        free(new_env);
        return;
    }
    new_env[env_len] = env_entry;
    new_env[env_len + 1] = NULL;
    free_old_env(shell->env);
    shell->env = new_env;
}
