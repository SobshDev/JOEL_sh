/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** Up key handler
*/

#include <string.h>
#include "minishell2.h"
#include "key_handler.h"

void handle_up_key(input_state_t *state)
{
    if (!state->shell->history->head)
        return;
    if (!state->shell->current_history_entry) {
        state->shell->current_history_entry = state->shell->history->tail;
    } else if (state->shell->current_history_entry->prev) {
        state->shell->current_history_entry =
        state->shell->current_history_entry->prev;
    }
    if (state->shell->current_history_entry) {
        memset(state->buffer, 0, BUFFER_SIZE);
        strcpy(state->buffer, state->shell->current_history_entry->command);
        state->buffer_pos = strlen(state->buffer);
        state->cursor_pos = state->buffer_pos;
        print_prompt(state);
    }
}
