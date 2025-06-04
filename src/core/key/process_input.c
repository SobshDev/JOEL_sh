/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** Process input character
*/

#include <unistd.h>
#include <stdlib.h>
#include "minishell2.h"
#include "key_handler.h"

static const key_func_t key_handlers[] = {
    {KEY_NEWLINE, NULL},
    {KEY_BACKSPACE, handle_backspace},
    {KEY_CLEAR, handle_clear_screen},
    {KEY_ESC, handle_escape_sequence},
    {KEY_CTRL_T, handle_toggle_history},
    {KEY_CTRL_I, handle_chatgpt},
    {KEY_CTRL_D, handle_ctrl_d},
    {0, NULL}
};

void process_input_char(input_state_t *state, char c)
{
    if (state->history_panel_visible) {
        if (c == KEY_CTRL_T)
            handle_toggle_history(state);
        return;
    }
    for (int i = 0; key_handlers[i].key; i++) {
        if (c == key_handlers[i].key && key_handlers[i].handler) {
            key_handlers[i].handler(state);
            return;
        }
    }
    if (c >= 32 && c < 127)
        handle_printable_char(state, c);
}
