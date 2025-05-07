/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** get_and_or_backg_token
*/

#include "token_getter.h"

static token_t get_and_token(lexer_t *lexer)
{
    token_t token = {
        .type = AND,
        .text_start = lexer->cursor,
        .text_len = 2
    };

    lexer->cursor += 2;
    return token;
}

static token_t get_backg_token(lexer_t *lexer)
{
    token_t token = {
        .type = BACKGROUND,
        .text_start = lexer->cursor,
        .text_len = 1
    };

    lexer->cursor += 1;
    return token;
}

token_t get_and_or_backg_token(lexer_t *lexer)
{
    if (lexer->cursor + 1 < lexer->len &&
        lexer->content[lexer->cursor + 1] == '&') {
        return get_and_token(lexer);
    }
    return get_backg_token(lexer);
}
