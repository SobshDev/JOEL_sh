/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** Backspace key handler
*/

#include <string.h>
#include "minishell2.h"
#include "key_handler.h"

void handle_backspace(input_state_t *state)
{
    if (state->cursor_pos > 0) {
        for (int i = state->cursor_pos - 1; i < state->buffer_pos - 1; i++) {
            state->buffer[i] = state->buffer[i + 1];
        }
        state->buffer_pos--;
        state->cursor_pos--;
        state->buffer[state->buffer_pos] = '\0';
        print_prompt(state);
    }
}
