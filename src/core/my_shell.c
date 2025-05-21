/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** my_shell
*/

#include "minishell2.h"
#include "my.h"

static void remove_newline(char *str)
{
    int len = my_strlen(str);

    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void my_tty_shell(shell_t *shell)
{
    execute_precmd(shell);
    read_tty_input(shell);
    remove_newline(shell->input);
    if (shell->input == NULL) {
        free_shell(shell);
        exit(84);
    }
    shell->special_vars->eofcount = 0;
    handle_cmd_line(shell);
}

void my_shell(shell_t *shell)
{
    execute_precmd(shell);
    while (read_input(shell)) {
        remove_newline(shell->input);
        if (shell->input == NULL) {
            free_shell(shell);
            exit(84);
        }
        handle_cmd_line(shell);
    }
    free_shell(shell);
    exit(shell->exit_value);
}
