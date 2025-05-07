/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** get_semicolon_token
*/

#include "../lexer.h"
#include "../token.h"
#include "token_getter.h"

token_t get_semicolon_token(lexer_t *lexer)
{
    token_t token = {
        .type = SEMICOLON,
        .text_start = lexer->cursor,
        .text_len = 1
    };

    lexer->cursor += 1;
    return token;
}
