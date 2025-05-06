/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** get_word_token
*/

#include "token_getter.h"
#include <stdbool.h>
#include <ctype.h>

static const keyword_t keywords[] = {
    {"if", IF},
    {"then", THEN},
    {"elif", ELIF},
    {"else", ELSE},
    {"fi", FI},
    {"while", WHILE},
    {"do", DO},
    {"done", DONE},
    {NULL, UNKNOWN}
};

static bool is_char_in_str(char c, char const *chars)
{
    for (int i = 0; chars[i]; i++) {
        if (c == chars[i])
            return true;
    }
    return false;
}

static token_t check_keyword_token(lexer_t *lexer, token_t token)
{
    char *word = NULL;

    if (token.type != WORD || token.text_len == 0)
        return token;
    word = strndup(lexer->content + token.text_start, token.text_len);
    if (!word)
        return token;
    for (int i = 0; keywords[i].keyword != NULL; i++) {
        if (strcmp(word, keywords[i].keyword) == 0) {
            token.type = keywords[i].type;
            break;
        }
    }
    free(word);
    return token;
}

static token_t get_special_word_token(lexer_t *lexer, token_t token, char c)
{
    if (c == '\'')
        token.is_quoted = true;
    if (c == '`')
        token.is_backticked = true;
    lexer->cursor += 1;
    token.text_start = lexer->cursor;
    while (lexer->content[lexer->cursor] != c) {
        if (lexer->content[lexer->cursor] == '\0') {
            token.type = UNKNOWN;
            return token;
        }
        token.text_len += 1;
        lexer->cursor += 1;
    }
    lexer->cursor += 1;
    return token;
}

token_t get_word_token(lexer_t *lexer)
{
    token_t token = {
        .type = WORD,
        .text_start = lexer->cursor,
        .text_len = 0
    };

    if (lexer->content[lexer->cursor] == '"' ||
        lexer->content[lexer->cursor] == '\'' ||
        lexer->content[lexer->cursor] == '`')
        return get_special_word_token(lexer, token,
            lexer->content[lexer->cursor]);
    while (lexer->cursor < lexer->len &&
        !isspace(lexer->content[lexer->cursor]) &&
        !is_char_in_str(lexer->content[lexer->cursor], ";|&><\"'()=")) {
        token.text_len += 1;
        lexer->cursor += 1;
    }
    return check_keyword_token(lexer, token);
}
