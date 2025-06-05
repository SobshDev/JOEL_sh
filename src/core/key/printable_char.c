/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** Printable character handler
*/

#include <string.h>
#include "minishell2.h"
#include "key_handler.h"

void handle_printable_char(input_state_t *state, char c)
{
    if (state->buffer_pos < BUFFER_SIZE - 1) {
        for (int i = state->buffer_pos; i > state->cursor_pos; i--) {
            state->buffer[i] = state->buffer[i - 1];
        }
        state->buffer[state->cursor_pos] = c;
        state->buffer_pos++;
        state->cursor_pos++;
        state->buffer[state->buffer_pos] = '\0';
        print_prompt(state);
    }
}
