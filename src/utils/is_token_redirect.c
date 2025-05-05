/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** is_token_redirect
*/

#include "parser.h"
#include "utils.h"

bool is_token_redirect(token_type_t type)
{
    if (type == REDIRECT_IN || type == REDIRECT_OUT ||
        type == HEREDOC || type == REDIRECT_APPEND ||
        type == REDIRECT_ERROR || type == REDIRECT_BOTH)
        return true;
    return false;
}
