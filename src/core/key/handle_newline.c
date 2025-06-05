/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle_newline
*/

#include "key_handler.h"

void handle_newline(input_state_t *state)
{
    (void)state;
    write(STDOUT_FILENO, "\n", 1);
}
