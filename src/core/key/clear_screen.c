/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** Clear screen key handler
*/

#include <unistd.h>
#include "minishell2.h"
#include "key_handler.h"

void handle_clear_screen(input_state_t *state)
{
    write(STDOUT_FILENO, "\033[H\033[J", 6);
    print_prompt(state);
}
