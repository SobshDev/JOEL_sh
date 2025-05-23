/*
** EPITECH PROJECT, 2025
** expand_globbings
** File description:
** Project Description
*/

#include <glob.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "minishell2.h"


static bool has_glob_chars(const char *str)
{
    return strpbrk(str, "*?[]") != NULL;
}

static int append_arg(char ***args, int argc, const char *value)
{
    char **tmp = realloc(*args, sizeof(char *) * (argc + 1));

    if (!tmp)
        return argc;
    *args = tmp;
    (*args)[argc] = strdup(value);
    argc++;
    return argc;
}

static int expand_one_glob(const char *pattern, char ***args, int argc)
{
    glob_t results;

    if (glob(pattern, 0, NULL, &results) == 0) {
        for (size_t j = 0; j < results.gl_pathc; ++j)
            argc = append_arg(args, argc, results.gl_pathv[j]);
        globfree(&results);
    } else
        argc = append_arg(args, argc, pattern);
    return argc;
}

static void free_args(char **args, int argc)
{
    for (int i = 0; i < argc; ++i)
        free(args[i]);
    free(args);
}

static void replace_node_args(node_t *node, char **new_args, int new_argc)
{
    char **tmp = realloc(new_args, sizeof(char *) * (new_argc + 1));

    if (tmp) {
        new_args = tmp;
        new_args[new_argc] = NULL;
    }
    free_args(node->args, node->arg_count);
    node->args = new_args;
    node->arg_count = new_argc;
}

void expand_globbing(node_t *node)
{
    int new_argc = 0;
    char **new_args = NULL;

    for (int i = 0; i < node->arg_count; ++i) {
        if (has_glob_chars(node->args[i]))
            new_argc = expand_one_glob(node->args[i], &new_args, new_argc);
        else
            new_argc = append_arg(&new_args, new_argc, node->args[i]);
    }
    replace_node_args(node, new_args, new_argc);
}
