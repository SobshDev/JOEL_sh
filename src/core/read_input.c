/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** read_input
*/

#include "minishell2.h"
#include "my.h"
#include "font.h"

void read_tty_input(shell_t *shell)
{
    handle_key_input(shell);
    if (!shell->input) {
        free_shell(shell);
        exit(0);
    }
}

bool read_input(shell_t *shell)
{
    size_t len = 0;
    ssize_t read;

    if (shell->input)
        free(shell->input);
    read = getline(&shell->input, &len, stdin);
    if (read == -1) {
        return false;
    }
    return true;
}
