/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** Left key handler
*/

#include "minishell2.h"
#include "key_handler.h"

void handle_left_key(input_state_t *state)
{
    if (state->cursor_pos > 0) {
        state->cursor_pos--;
        print_prompt(state);
    }
}
