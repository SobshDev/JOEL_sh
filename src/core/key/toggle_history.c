/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** Toggle history panel handler
*/

#include <unistd.h>
#include <stdio.h>
#include "minishell2.h"
#include "key_handler.h"
#include "my.h"
#include "font.h"

static void put_colored_str(int fd, char *color, char *str, char *reset)
{
    write(fd, color, my_strlen(color));
    write(fd, str, my_strlen(str));
    write(fd, reset, my_strlen(reset));
}

static void print_history_header_footer(int fd, bool is_header)
{
    if (is_header) {
        put_colored_str(fd, BCYAN, "╔══════════ History Panel"
        " ══════════╗\n", RESET);
    } else {
        put_colored_str(fd, BCYAN, "╚═════════════════════════"
        "══════════╝\n", RESET);
        put_colored_str(fd, BPURPLE, "    Press Ctrl+T "
        "to return to shell    \n", RESET);
    }
}

static void print_history_entries(input_state_t *state, int start_index)
{
    history_entry_t *entry = state->shell->history->head;
    char buffer[BUFFER_SIZE];

    for (int i = 0; i < start_index && entry; i++)
        entry = entry->next;
    while (entry) {
        snprintf(buffer, BUFFER_SIZE, " %3d │ %s\n",
        entry->id, entry->command);
        put_colored_str(STDOUT_FILENO, BIYELLOW, buffer, RESET);
        entry = entry->next;
    }
}

static void display_history_panel(input_state_t *state)
{
    int max_entries = 10;
    int start_index;

    write(STDOUT_FILENO, "\033[s\033[H\033[2J", 10);
    print_history_header_footer(STDOUT_FILENO, true);
    if (!state->shell->history || state->shell->history->count == 0) {
        put_colored_str(STDOUT_FILENO, BRED, "       History "
        "is empty.       \n", RESET);
        print_history_header_footer(STDOUT_FILENO, false);
        return;
    }
    start_index = (state->shell->history->count > max_entries) ?
        (state->shell->history->count - max_entries) : 0;
    print_history_entries(state, start_index);
    print_history_header_footer(STDOUT_FILENO, false);
    write(STDOUT_FILENO, "\033[u", 3);
}

static void clear_screen_and_redraw(input_state_t *state)
{
    write(STDOUT_FILENO, "\033[H", 3);
    write(STDOUT_FILENO, "\033[2J", 4);
    print_prompt(state);
    write(STDOUT_FILENO, state->buffer, state->buffer_pos);
}

void handle_toggle_history(input_state_t *state)
{
    state->history_panel_visible = !state->history_panel_visible;
    if (state->history_panel_visible)
        display_history_panel(state);
    else
        clear_screen_and_redraw(state);
}
