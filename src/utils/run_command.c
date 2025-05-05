/*
** EPITECH PROJECT, 2025
** B-PSU-200-MPL-2-1-42sh-louis.bagnol
** File description:
** run_command
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *append_to_output(char *output, char *buffer, size_t *output_size)
{
    size_t bytes_read = strlen(buffer);
    char *new_output = realloc(output, *output_size + bytes_read + 1);

    if (new_output == NULL) {
        free(output);
        return NULL;
    }
    output = new_output;
    strcpy(output + *output_size, buffer);
    *output_size += bytes_read;
    return output;
}

static char *handle_empty_output(char *output)
{
    if (output == NULL) {
        output = strdup("");
        if (output == NULL)
            return NULL;
    }
    return output;
}

static char *process_command_output(FILE *fp)
{
    char *output = NULL;
    char buffer[BUFSIZ];
    size_t output_size = 0;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        output = append_to_output(output, buffer, &output_size);
        if (output == NULL)
            return NULL;
    }
    return handle_empty_output(output);
}

char *run_command(char *command)
{
    FILE *fp;
    char *output = NULL;

    fp = popen(command, "r");
    if (fp == NULL)
        return NULL;
    output = process_command_output(fp);
    pclose(fp);
    return output;
}
