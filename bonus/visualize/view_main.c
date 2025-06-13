/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** view_main
*/

#include "../src/lexer/lexer.h"
#include "parser.h"
#include "my.h"

#define MAX_INPUT_SIZE 16000

static char *read_user_input(void)
{
    char *buffer = malloc(MAX_INPUT_SIZE);
    size_t size = MAX_INPUT_SIZE;
    ssize_t read;

    if (!buffer)
        return NULL;
    printf("Enter command to visualize: ");
    fflush(stdout);
    if ((read = getline(&buffer, &size, stdin)) == -1) {
        free(buffer);
        return NULL;
    }
    if (read > 0 && buffer[read - 1] == '\n')
        buffer[read - 1] = '\0';
    return buffer;
}

int main(int argc, char **argv)
{
    parser_t *parser;
    char *input = NULL;

    if (argc > 1 || !argv[0])
        return 84;
    input = read_user_input();
    if (!input)
        return 84;
    printf("\nVisualizing command: %s\n\n", input);
    parser = create_parser(input);
    if (!parser)
        return 84;
    print_token_stream(parser->lexer);
    parser->root = parse(parser);
    print_ast(parser);
    destroy_parser(parser);
    return 0;
}
