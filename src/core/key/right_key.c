/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** Right key handler
*/

#include "minishell2.h"
#include "key_handler.h"

void handle_right_key(input_state_t *state)
{
    if (state->cursor_pos < state->buffer_pos) {
        state->cursor_pos++;
        print_prompt(state);
    }
}
