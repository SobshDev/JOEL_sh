/*
** EPITECH PROJECT, 2025
** B-PSU-200-MPL-2-1-42sh-louis.bagnol
** File description:
** get_context
*/

#include <stdlib.h>
#include <string.h>
#include "minishell2.h"
#include "chatgpt.h"

static void free_command_outputs(char **outputs, int count)
{
    for (int i = 0; i < count; i++) {
        if (outputs[i]) {
            free(outputs[i]);
        }
    }
}

static void get_command_results(char **command_outputs)
{
    command_outputs[0] = run_command("pwd");
    command_outputs[1] = run_command("whoami");
    command_outputs[2] = run_command("cat /etc/os-release 2>/dev/null"
    "| grep PRETTY_NAME | cut -d'\"' -f2 || hostname");
    command_outputs[3] = run_command("ls -la | head -10");
    command_outputs[4] = run_command("env | grep -E 'USER|HOME|PWD|SHELL"
    "|TERM|PATH' | head -6");
}

static char *build_context_string(char **command_outputs)
{
    char *context = NULL;
    size_t context_size = 0;
    const char *labels[] = {
        "Working directory: ", "User: ", "Host: ",
        "Files in current directory: ", "Environment: "
    };

    for (int i = 0; i < 5; i++) {
        context_size += strlen(labels[i]);
        context_size += command_outputs[i] ? strlen(command_outputs[i]) : 0;
    }
    context = malloc(context_size + 1);
    if (context) {
        context[0] = '\0';
        for (int i = 0; i < 5; i++) {
            strcat(context, labels[i]);
            strcat(context, command_outputs[i] ? command_outputs[i] : "");
        }
    }
    return context;
}

char *get_context(void)
{
    char *command_outputs[5] = {NULL};
    char *context = NULL;

    get_command_results(command_outputs);
    context = build_context_string(command_outputs);
    free_command_outputs(command_outputs, 5);
    return context;
}
