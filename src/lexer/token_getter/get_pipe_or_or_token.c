/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** get_pipe_or_or_token
*/

#include "token_getter.h"

static token_t get_pipe_token(lexer_t *lexer)
{
    token_t token = {
        .type = PIPE,
        .text_start = lexer->cursor,
        .text_len = 1
    };

    lexer->cursor += 1;
    return token;
}

static token_t get_or_token(lexer_t *lexer)
{
    token_t token = {
        .type = OR,
        .text_start = lexer->cursor,
        .text_len = 2
    };

    lexer->cursor += 2;
    return token;
}

token_t get_pipe_or_or_token(lexer_t *lexer)
{
    if (lexer->cursor + 1 < lexer->len &&
        lexer->content[lexer->cursor + 1] == '|') {
        return get_or_token(lexer);
    }
    return get_pipe_token(lexer);
}
