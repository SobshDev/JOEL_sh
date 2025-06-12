/*
** EPITECH PROJECT, 2025
** expland_alias
** File description:
** Project Description
*/

#include "minishell2.h"
#include "my.h"
#include "utils.h"

static void my_free_array(char **array)
{
    if (array) {
        for (int i = 0; array[i] != NULL; i++)
            free(array[i]);
        free(array);
    }
}

static char **split_alias_value(const char *value)
{
    char **alias_parts = my_str_to_word_array(value, " \t");

    if (!alias_parts || !alias_parts[0]) {
        my_free_array(alias_parts);
        return NULL;
    }
    return alias_parts;
}

static char **merge_args_with_alias(char **alias_parts, char **args)
{
    int alias_len = my_arraylen(alias_parts);
    int args_len = my_arraylen(args);
    char **new_args = malloc(sizeof(char *) * (args_len + alias_len));

    if (!new_args) {
        perror("malloc");
        exit(84);
    }
    for (int j = 0; j < alias_len; j++)
        new_args[j] = strdup(alias_parts[j]);
    for (int j = 1; j < args_len; j++)
        new_args[alias_len + j - 1] = args[j];
    new_args[alias_len + args_len - 1] = NULL;
    return new_args;
}

static void replace_args_with_alias(node_t *node, char **alias_parts)
{
    char **new_args;

    if (!alias_parts)
        return;
    new_args = merge_args_with_alias(alias_parts, node->args);
    free(node->args[0]);
    free(node->args);
    node->args = new_args;
    my_free_array(alias_parts);
}

static bool contains_separators(const char *value)
{
    return (strchr(value, ';') || strchr(value, '&') || strchr(value, '|') ||
            strchr(value, '(') || strchr(value, ')') || strchr(value, '<') ||
            strchr(value, '>'));
}

static void handle_alias_expansion(node_t *node, alias_t *alias)
{
    char **alias_parts = NULL;

    if (contains_separators(alias->value)) {
        system(alias->value);
        node->args[0] = NULL;
    } else {
        alias_parts = split_alias_value(alias->value);
        replace_args_with_alias(node, alias_parts);
    }
}

void expand_aliases(shell_t *shell, node_t *node)
{
    alias_t **aliases = shell->aliases;

    if (!aliases || !node->args || !node->args[0])
        return;
    for (int i = 0; aliases[i] != NULL; i++) {
        if (strcmp(aliases[i]->name, node->args[0]) == 0) {
            handle_alias_expansion(node, aliases[i]);
            return;
        }
    }
}
