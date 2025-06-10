/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** print_history
*/

#include "minishell2.h"
#include "my.h"

void print_history(history_t *history, int num_entries)
{
    history_entry_t *current;
    int start_id;

    if (history->count == 0) {
        my_putstr("History is empty.\n");
        return;
    }
    if (num_entries == 0)
        num_entries = history->count;
    start_id = (history->count > num_entries) ?
            (history->count - num_entries + 1) : 1;
    current = history->head;
    while (current != NULL) {
        if (current->id >= start_id)
            my_printf("%5d  %s\n", current->id, current->command);
        current = current->next;
    }
}

void my_history(shell_t *shell, node_t *node)
{
    int num_entries = 0;

    if (node->args[1] != NULL)
        num_entries = my_getnbr(node->args[1]);
    if (num_entries < 0) {
        my_putstr("history: invalid option\n");
        return;
    }
    print_history(shell->history, num_entries);
}
