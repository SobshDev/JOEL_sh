/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle_ctrl_d
*/

#include "key_handler.h"

void handle_ctrl_d(input_state_t *state)
{
    state->shell->special_vars->eofcount += 1;
    if (state->shell->special_vars->eofcount <
        state->shell->special_vars->ignoreeof) {
        write(STDOUT_FILENO, "\n", 1);
        return;
    }
    write(STDOUT_FILENO, "exit\n", 5);
    free_shell(state->shell);
    exit(0);
}
