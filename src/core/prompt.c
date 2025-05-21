/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** Prompt display and handling
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell2.h"
#include "my.h"
#include "font.h"

char *get_git_branch(void)
{
    FILE *fp = popen("git rev-parse --abbrev-ref HEAD 2>/dev/null", "r");
    char *branch = NULL;
    size_t size = 0;

    if (!fp)
        return NULL;
    if (getline(&branch, &size, fp) == -1) {
        pclose(fp);
        if (branch)
            free(branch);
        return NULL;
    }
    pclose(fp);
    if (branch) {
        branch[strcspn(branch, "\n")] = 0;
    }
    return branch;
}

int get_prompt_len(char *user, char *home, char *path)
{
    int len = (user ? strlen(user) : 0) + 4;
    char *branch = get_git_branch();

    len += (path && home ? strlen(path) - strlen(home) : 0);
    if (branch) {
        len += strlen(branch) + 3;
        free(branch);
    }
    return len;
}

void print_username(char *user)
{
    write(STDOUT_FILENO, UGREEN, strlen(UGREEN));
    if (user)
        write(STDOUT_FILENO, user, strlen(user));
    write(STDOUT_FILENO, COLOR_OFF, strlen(COLOR_OFF));
    write(STDOUT_FILENO, ":~", 2);
}

static void print_path(char *path, char *home)
{
    write(STDOUT_FILENO, BBLUE, strlen(BBLUE));
    if (path && home && strlen(path) >= strlen(home) &&
        strncmp(path, home, strlen(home)) == 0) {
        write(STDOUT_FILENO, path + strlen(home), strlen(path) - strlen(home));
    } else if (path) {
        write(STDOUT_FILENO, path, strlen(path));
    }
    write(STDOUT_FILENO, COLOR_OFF, strlen(COLOR_OFF));
}

static void print_git_branch(void)
{
    char *branch = get_git_branch();

    if (branch) {
        write(STDOUT_FILENO, " ", 1);
        write(STDOUT_FILENO, BYELLOW, strlen(BYELLOW));
        write(STDOUT_FILENO, "(", 1);
        write(STDOUT_FILENO, branch, strlen(branch));
        write(STDOUT_FILENO, ")", 1);
        write(STDOUT_FILENO, COLOR_OFF, strlen(COLOR_OFF));
        free(branch);
    }
}

static void print_buffer(input_state_t *state, int position)
{
    write(STDOUT_FILENO, "> ", 2);
    write(STDOUT_FILENO, state->buffer, strlen(state->buffer));
    write(STDOUT_FILENO, "\033[K", 3);
    dprintf(STDOUT_FILENO, "\r\033[%dC", position);
}

void print_prompt(input_state_t *state)
{
    char *path = my_getenv(state->shell->env, "PWD");
    char *user = my_getenv(state->shell->env, "HOST");
    char *home = my_getenv(state->shell->env, "HOME");
    int prompt_len = get_prompt_len(user, home, path);
    int position = prompt_len + state->cursor_pos;

    write(STDOUT_FILENO, "\r", 1);
    print_username(user);
    print_path(path, home);
    print_git_branch();
    print_buffer(state, position);
}

void initialize_input_state(input_state_t *state, shell_t *shell)
{
    memset(state->buffer, 0, BUFFER_SIZE);
    state->buffer_pos = 0;
    state->cursor_pos = 0;
    state->shell = shell;
    state->shell->current_history_entry = NULL;
    state->history_panel_visible = false;
}
