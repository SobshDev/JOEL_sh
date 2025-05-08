/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** get_redirect_token
*/

#include "token_getter.h"
#include <stdbool.h>

static bool is_redir_input(char c)
{
    return c == '<';
}

static bool is_redir_output(char c)
{
    return c == '>';
}

static token_t get_redirect_in(lexer_t *lexer, token_t token)
{
    if (lexer->cursor + 1 < lexer->len &&
        is_redir_input(lexer->content[lexer->cursor + 1])) {
        token.type = HEREDOC;
        token.text_len = 2;
        lexer->cursor += 2;
    } else {
        token.type = REDIRECT_IN;
        lexer->cursor += 1;
    }
    return token;
}

static token_t get_redirect_out(lexer_t *lexer, token_t token)
{
    if (lexer->cursor + 1 < lexer->len &&
        is_redir_output(lexer->content[lexer->cursor + 1])) {
        token.type = REDIRECT_APPEND;
        token.text_len = 2;
        lexer->cursor += 2;
    } else {
        token.type = REDIRECT_OUT;
        lexer->cursor += 1;
    }
    return token;
}

token_t get_redirect_token(lexer_t *lexer)
{
    token_t token = {
        .type = UNKNOWN,
        .text_start = lexer->cursor,
        .text_len = 1
    };

    if (is_redir_input(lexer->content[lexer->cursor]))
        token = get_redirect_in(lexer, token);
    if (is_redir_output(lexer->content[lexer->cursor]))
        token = get_redirect_out(lexer, token);
    return token;
}
