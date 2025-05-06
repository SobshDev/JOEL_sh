/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** token
*/

#include "lexer.h"
#include "font.h"

static const char *TOKEN_TYPE_STRINGS[] = {
    [UNKNOWN] = "UNKNOWN",
    [WORD] = "WORD",
    [SEMICOLON] = "SEMICOLON",
    [PIPE] = "PIPE",
    [REDIRECT_IN] = "REDIRECT_IN",
    [REDIRECT_OUT] = "REDIRECT_OUT",
    [HEREDOC] = "HEREDOC",
    [REDIRECT_APPEND] = "REDIRECT_APPEND",
    [REDIRECT_ERROR] = "REDIRECT_ERROR",
    [REDIRECT_BOTH] = "REDIRECT_BOTH",
    [OR] = "OR",
    [AND] = "AND",
    [BACKGROUND] = "BACKGROUND",
    [LPAREN] = "LPAREN",
    [RPAREN] = "RPAREN",
    [IF] = "IF",
    [THEN] = "THEN",
    [ELIF] = "ELIF",
    [ELSE] = "ELSE",
    [FI] = "FI",
    [WHILE] = "WHILE",
    [DO] = "DO",
    [DONE] = "DONE",
    [EQUALS] = "EQUALS",
    [END] = "END"
};

static char *token_type_to_str(token_type_t type)
{
    return (char *)TOKEN_TYPE_STRINGS[type];
}

void print_token(lexer_t *lexer, token_t token)
{
    if (token.type == END) {
        printf("%sEND%s: %s\\0%s\n\n", BLUE, RESET, BOLD, RESET);
        return;
    }
    printf("%s%s%s: %s%.*s%s\n",
        BLUE,
        token_type_to_str(token.type),
        RESET,
        BOLD,
        (int)token.text_len,
        lexer->content + token.text_start,
        RESET
    );
}

void print_token_stream(lexer_t *lexer)
{
    size_t saved_cursor = lexer->cursor;
    token_t token;

    lexer->cursor = 0;
    token = next_token(lexer);
    printf("%s=== %sTOKEN STREAM%s ===%s\n",
        BOLD GREEN, UNDERLINE, RESET BOLD GREEN, RESET);
    while (token.type != END) {
        print_token(lexer, token);
        token = next_token(lexer);
    }
    print_token(lexer, token);
    lexer->cursor = saved_cursor;
}
