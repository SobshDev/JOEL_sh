/*
** EPITECH PROJECT, 2025
** my_alias
** File description:
** Project Description
*/

#include "minishell2.h"
#include "my.h"

int get_alias_count(alias_t **aliases)
{
    int count = 0;

    if (!aliases)
        return 0;
    for (int i = 0; aliases[i] != NULL; i++)
        count++;
    return count;
}

static alias_t *create_new_alias(char *name, char *value)
{
    alias_t *new_alias = malloc(sizeof(alias_t));

    if (!new_alias) {
        perror("malloc");
        exit(84);
    }
    new_alias->name = strdup(name);
    new_alias->value = strdup(value);
    if (!new_alias->name || !new_alias->value) {
        if (new_alias->name)
            free(new_alias->name);
        if (new_alias->value)
            free(new_alias->value);
        free(new_alias);
        return NULL;
    }
    return new_alias;
}

void add_alias(shell_t *shell, char *name, char *value)
{
    alias_t **aliases = shell->aliases;
    int len = get_alias_count(aliases);

    for (int i = 0; i < len; i++) {
        if (strcmp(aliases[i]->name, name) == 0) {
            free(aliases[i]->value);
            aliases[i]->value = strdup(value);
            return;
        }
    }
    aliases = realloc(aliases, sizeof(alias_t *) * (len + 2));
    if (!aliases) {
        perror("realloc");
        exit(84);
    }
    shell->aliases = aliases;
    aliases[len] = create_new_alias(name, value);
    aliases[len + 1] = NULL;
}

void list_aliases(shell_t *shell)
{
    alias_t **aliases = shell->aliases;

    if (!aliases || !aliases[0]) {
        my_putstr_err("alias: No aliases found.\n");
        return;
    }
    for (int i = 0; aliases[i] != NULL; i++) {
        my_putstr(aliases[i]->name);
        my_putstr("='");
        my_putstr(aliases[i]->value);
        my_putstr("'\n");
    }
}

static void add_alias_from_argument(shell_t *shell, char *arg)
{
    char *name = strtok(arg, "=");
    char *value = strtok(NULL, "=");
    int name_len = 0;

    if (name == NULL || value == NULL) {
        my_putstr_err("alias: Invalid alias format.\n");
        return;
    }
    name_len = my_strlen(name);
    if (name[name_len - 1] == '=')
        name[name_len - 1] = '\0';
    add_alias(shell, name, value);
}

void add_alias_with_name_and_value(shell_t *shell,
    char *name, char *value)
{
    int name_len = my_strlen(name);

    if (name[name_len - 1] == '=')
        name[name_len - 1] = '\0';
    if (name[0] == '\0') {
        my_putstr_err("alias: Invalid alias name.\n");
        return;
    }
    add_alias(shell, name, value);
}

void my_alias(shell_t *shell, node_t *node)
{
    int len = my_arraylen(node->args);
    char *combined = NULL;

    if (len == 1)
        return list_aliases(shell);
    if (len == 2) {
        if (strchr(node->args[1], '=') == NULL)
            return my_putstr_err("alias: Invalid alias format.\n");
        return add_alias_from_argument(shell, node->args[1]);
    }
    if (len == 4 && strcmp(node->args[2], "=") == 0) {
        combined = my_strcat(node->args[1], "=");
        combined = my_strcat(combined, node->args[3]);
        return add_alias_from_argument(shell, combined);
    }
    if (len > 3)
        return my_putstr_err("alias: Too many arguments.\n");
    if (strchr(node->args[1], '=') == NULL)
        return my_putstr_err("alias: Invalid alias format.\n");
    add_alias_with_name_and_value(shell, node->args[1], node->args[2]);
}
