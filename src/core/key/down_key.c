/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** Down key handler
*/

#include <string.h>
#include "minishell2.h"
#include "key_handler.h"

void handle_down_key(input_state_t *state)
{
    if (!state->shell->current_history_entry)
        return;
    state->shell->current_history_entry =
    state->shell->current_history_entry->next;
    if (state->shell->current_history_entry) {
        memset(state->buffer, 0, BUFFER_SIZE);
        strcpy(state->buffer, state->shell->current_history_entry->command);
        state->buffer_pos = strlen(state->buffer);
        state->cursor_pos = state->buffer_pos;
    } else {
        memset(state->buffer, 0, BUFFER_SIZE);
        state->buffer_pos = 0;
        state->cursor_pos = 0;
    }
    print_prompt(state);
}
