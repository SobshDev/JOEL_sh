/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** get_history_entry
*/

#include "minishell2.h"
#include "my.h"

history_entry_t *get_history_entry(history_t *history, int id)
{
    history_entry_t *current = history->head;

    if (id <= 0 || id > history->count)
        return NULL;
    while (current) {
        if (current->id == id)
            return current;
        current = current->next;
    }
    return NULL;
}
