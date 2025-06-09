/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** Home key handler
*/

#include "minishell2.h"
#include "key_handler.h"

void handle_home_key(input_state_t *state)
{
    state->cursor_pos = 0;
    print_prompt(state);
}
