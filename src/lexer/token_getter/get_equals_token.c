/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** get_equals_token
*/

#include "token_getter.h"

token_t get_equals_token(lexer_t *lexer)
{
    token_t token = {
        .type = EQUALS,
        .text_start = lexer->cursor,
        .text_len = 1
    };

    lexer->cursor += 1;
    return token;
}
