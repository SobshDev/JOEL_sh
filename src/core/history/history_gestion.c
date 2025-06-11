/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** history_gestion
*/

#include "minishell2.h"

history_t *create_history(void)
{
    history_t *history = malloc(sizeof(history_t));

    if (!history)
        return (NULL);
    history->head = NULL;
    history->tail = NULL;
    history->count = 0;
    return history;
}

void destroy_history(history_t *history)
{
    history_entry_t *current = history->head;
    history_entry_t *next;

    while (current) {
        next = current->next;
        free(current->command);
        free(current);
        current = next;
    }
    free(history);
}
