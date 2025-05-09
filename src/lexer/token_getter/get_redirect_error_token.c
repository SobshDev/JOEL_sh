/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** get_redirect_error_token
*/

#include "token_getter.h"

token_t get_redirect_error_token(lexer_t *lexer)
{
    token_t token = {
        .type = REDIRECT_ERROR,
        .text_start = lexer->cursor,
        .text_len = 2
    };

    lexer->cursor += 2;
    return token;
}
