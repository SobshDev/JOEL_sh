/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** End key handler
*/

#include "minishell2.h"
#include "key_handler.h"

void handle_end_key(input_state_t *state)
{
    state->cursor_pos = state->buffer_pos;
    print_prompt(state);
}
