/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** expand_history
*/

#include "minishell2.h"
#include "my.h"

static char *handle_bang_bang(shell_t *shell, char *expanded_command)
{
    if (my_strcmp(shell->input, "!!") == 0) {
        if (shell->history->tail) {
            expanded_command = my_strdup(shell->history->tail->command);
            my_printf("%s\n", expanded_command);
        } else {
            my_putstr("!!: Event not found.\n");
            shell->history_expansion_failed = true;
        }
    }
    return expanded_command;
}

static char *handle_bang_number(shell_t *shell, char *expanded_command)
{
    int id = 0;
    history_entry_t *entry = NULL;

    if (shell->input[0] == '!' && my_str_isnum(&shell->input[1])) {
        id = my_getnbr(shell->input + 1);
        entry = get_history_entry(shell->history, id);
        if (entry) {
            expanded_command = my_strdup(entry->command);
            my_printf("%s\n", expanded_command);
        } else {
            my_printf("!%s: Event not found.\n", &shell->input[1]);
            shell->history_expansion_failed = true;
        }
    }
    return expanded_command;
}

void expand_history(shell_t *shell)
{
    char *expanded_command = NULL;

    if (!shell->input || shell->input[0] == '\0' ||
        !shell->history || shell->history->count == 0)
        return;
    expanded_command = handle_bang_bang(shell, expanded_command);
    if (expanded_command == NULL)
        expanded_command = handle_bang_number(shell, expanded_command);
    if (expanded_command) {
        free(shell->input);
        shell->input = expanded_command;
    }
}
