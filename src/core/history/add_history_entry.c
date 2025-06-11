/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** add_history_entry
*/

#include "minishell2.h"
#include "my.h"

static void add_to_linked_list(history_t *history,
    history_entry_t *new_entry, const char *command)
{
    new_entry->command = my_strdup(command);
    if (!new_entry->command) {
        free(new_entry);
        return;
    }
    history->count += 1;
    new_entry->id = history->count;
    new_entry->next = NULL;
    new_entry->prev = history->tail;
    if (history->tail)
        history->tail->next = new_entry;
    else
        history->head = new_entry;
    history->tail = new_entry;
}

void add_history_entry(history_t *history, const char *command)
{
    history_entry_t *new_entry = malloc(sizeof(history_entry_t));

    if (!new_entry || !command || !command[0])
        return;
    if (history->count > 0 && history->tail &&
        my_strcmp(history->tail->command, command) == 0) {
        free(new_entry);
        return;
    }
    add_to_linked_list(history, new_entry, command);
}
