/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** get_end_token
*/

#include "../lexer.h"
#include "../token.h"
#include "token_getter.h"

token_t get_end_token(lexer_t *lexer)
{
    token_t token = {
        .type = END,
        .text_start = lexer->cursor,
        .text_len = 1
    };

    return token;
}
