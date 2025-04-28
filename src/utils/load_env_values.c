/*
** EPITECH PROJECT, 2025
** B-PSU-200-MPL-2-1-42sh-louis.bagnol
** File description:
** load_env_values
*/

#include "minishell2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int get_env_count(env_value_t **env)
{
    int i = 0;

    if (!env)
        return (0);
    while (env[i])
        i++;
    return i;
}

static env_value_t **copy_old_env(env_value_t **env)
{
    env_value_t **new_env = malloc(sizeof(env_value_t *) *
    (get_env_count(env) + 2));
    int i = 0;

    if (!new_env)
        return (NULL);
    if (env) {
        for (i = 0; env[i]; i++)
            new_env[i] = env[i];
    }
    new_env[i] = NULL;
    new_env[i + 1] = NULL;
    free(env);
    return (new_env);
}

static env_value_t *get_env_value(const char *str, FILE *f)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read = getline(&line, &len, f);
    env_value_t *new_env_value = malloc(sizeof(env_value_t));

    while (read != -1) {
        if (strncmp(str, line, strlen(str)) == 0) {
            new_env_value->env = strdup(str);
            new_env_value->value = strdup(line + strlen(str) + 1);
            break;
        }
        read = getline(&line, &len, f);
    }
    if (line)
        free(line);
    return (new_env_value);
}

static env_value_t **append_env_value(const char *str, env_value_t **env)
{
    FILE *f = fopen(".env", "r");
    env_value_t **new_env = copy_old_env(env);

    if (!f || !new_env)
        return NULL;
    new_env[get_env_count(new_env)] = get_env_value(str, f);
    fclose(f);
    return new_env;
}

env_value_t **get_env_values(void)
{
    env_value_t **env = NULL;

    env = append_env_value("OPENAI_API_KEY", env);
    env = append_env_value("OPENAI_MODEL", env);
    return env;
}
