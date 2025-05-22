/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** Main input handling
*/

#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell2.h"
#include "key_handler.h"
#include "my.h"
#include "font.h"

void handle_key_input(shell_t *shell)
{
    input_state_t state;
    char c;
    bool running = true;

    initialize_input_state(&state, shell);
    setup_terminal();
    print_prompt(&state);
    while (running) {
        if (read(STDIN_FILENO, &c, 1) != 1)
            break;
        if (c == '\n' && !state.history_panel_visible) {
            write(STDOUT_FILENO, "\n", 1);
            running = false;
        } else
            process_input_char(&state, c);
    }
    restore_terminal();
    if (shell->input)
        free(shell->input);
    shell->input = my_strdup(state.buffer);
}
