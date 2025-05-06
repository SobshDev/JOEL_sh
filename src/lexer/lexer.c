/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** lexer
*/

#include "lexer.h"
#include "token_getter/token_getter.h"
#include <ctype.h>

/*
    0x28 = '('
    0x29 = ')'
    0x3D = '='

    We cant use the characters like this '(' because
    somehow it breaks the coding-style checker.
*/
static const token_handler_t token_handlers[] = {
    ['\0'] = get_end_token,
    [';'] = get_semicolon_token,
    ['|'] = get_pipe_or_or_token,
    ['&'] = get_and_or_backg_token,
    ['>'] = get_redirect_token,
    ['<'] = get_redirect_token,
    [0x28] = get_paren_token,
    [0x29] = get_paren_token,
    [0x3D] = get_equals_token
};

lexer_t *create_lexer(char *content)
{
    lexer_t *lexer = malloc(sizeof(lexer_t));

    if (!lexer)
        return NULL;
    lexer->content = content;
    lexer->cursor = 0;
    lexer->len = strlen(content);
    return lexer;
}

void destroy_lexer(lexer_t *lexer)
{
    if (lexer->content)
        free(lexer->content);
    if (lexer)
        free(lexer);
}

static token_t handle_special_tokens(lexer_t *lexer, token_t token)
{
    if (lexer->cursor + 1 < lexer->len &&
        lexer->content[lexer->cursor] == '2' &&
        lexer->content[lexer->cursor + 1] == '>')
        return get_redirect_error_token(lexer);
    if (lexer->cursor + 1 < lexer->len &&
        lexer->content[lexer->cursor] == '&' &&
        lexer->content[lexer->cursor + 1] == '>')
        return get_redirect_both_token(lexer);
    return token;
}

static token_t handle_normal_tokens(lexer_t *lexer, token_t token)
{
    unsigned char c = (unsigned char)lexer->content[lexer->cursor];

    if (c > 127)
        return token;
    if (!token_handlers[c])
        return get_word_token(lexer);
    return token_handlers[c](lexer);
}

static token_t get_token_logic(lexer_t *lexer, token_t token)
{
    token = handle_special_tokens(lexer, token);
    if (token.type != UNKNOWN)
        return token;
    token = handle_normal_tokens(lexer, token);
    return token;
}

static void lexer_skip_whitespace(lexer_t *lexer)
{
    while (isspace(lexer->content[lexer->cursor])) {
        lexer->cursor += 1;
    }
}

token_t next_token(lexer_t *lexer)
{
    token_t token = {0};

    lexer_skip_whitespace(lexer);
    token.text_start = lexer->cursor;
    if (lexer->cursor >= lexer->len)
        return get_end_token(lexer);
    token = get_token_logic(lexer, token);
    return token;
}

token_t peek_token(lexer_t *lexer)
{
    size_t cursor = lexer->cursor;
    token_t token = next_token(lexer);

    lexer->cursor = cursor;
    return token;
}
