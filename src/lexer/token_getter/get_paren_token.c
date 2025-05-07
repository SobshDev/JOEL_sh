/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** get_paren_token
*/

#include "token_getter.h"

token_t get_paren_token(lexer_t *lexer)
{
    token_t token = {
        .type = END,
        .text_start = lexer->cursor,
        .text_len = 1
    };

    if (lexer->content[lexer->cursor] == '(')
        token.type = LPAREN;
    if (lexer->content[lexer->cursor] == ')')
        token.type = RPAREN;
    lexer->cursor += 1;
    return token;
}
