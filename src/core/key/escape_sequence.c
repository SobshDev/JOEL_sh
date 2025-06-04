/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** Escape sequence handler
*/

#include <unistd.h>
#include "minishell2.h"
#include "key_handler.h"

static const esc_func_t esc_handlers[] = {
    {KEY_UP, handle_up_key},
    {KEY_DOWN, handle_down_key},
    {KEY_RIGHT, handle_right_key},
    {KEY_LEFT, handle_left_key},
    {KEY_HOME, handle_home_key},
    {KEY_END, handle_end_key},
    {0, NULL}
};

static bool handle_bracket_sequence(input_state_t *state)
{
    if (state->seq[1] == KEY_DELETE) {
        if (read(STDIN_FILENO, &state->seq[2], 1) != 1 || state->seq[2] != '~')
            return false;
        handle_delete_key(state);
        return true;
    }
    for (int i = 0; esc_handlers[i].handler; i++) {
        if (state->seq[1] == esc_handlers[i].key) {
            esc_handlers[i].handler(state);
            return true;
        }
    }
    return true;
}

void handle_escape_sequence(input_state_t *state)
{
    if (read(STDIN_FILENO, &state->seq[0], 1) != 1)
        return;
    if (read(STDIN_FILENO, &state->seq[1], 1) != 1)
        return;
    if (state->seq[0] == '[')
        handle_bracket_sequence(state);
    return;
}
