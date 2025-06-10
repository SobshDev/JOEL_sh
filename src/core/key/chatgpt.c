/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** ChatGPT integration handler
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell2.h"
#include "key_handler.h"
#include "chatgpt.h"

static char *get_baseprompt(void)
{
    char *baseprompt = strdup("You are an AI assistant integrated into a shell"
        " terminal. Your task is to respond ONLY with the exact command that "
        "best satisfies the user's request. DO NOT include explanations or ma"
        "rkdown formatting. Return just the raw command that can be executed "
        "directly in the shell. If multiple commands are needed, combine them "
        "with && or use a one-line script. If the request is unclear, provide "
        "the most likely command based on the context. "
        "\n\n--- SYSTEM CONTEXT ---\n");

    return baseprompt;
}

static char *create_prompt(const char *base_prompt, const char *context,
    const char *question)
{
    size_t message_size = strlen(base_prompt) + (context ? strlen(context) : 0)
    + strlen("\n\n--- USER REQUEST ---\n") + strlen(question) + 1;
    char *message = malloc(message_size);

    if (!message)
        return NULL;
    strcpy(message, base_prompt);
    if (context)
        strcat(message, context);
    strcat(message, "\n\n--- USER REQUEST ---\n");
    strcat(message, question);
    return message;
}

static char *get_chargpt_response(char *question, shell_t *shell)
{
    char *context = NULL;
    char *message = NULL;
    char *response = NULL;
    char *baseprompt = get_baseprompt();

    context = get_context();
    message = create_prompt(baseprompt, context, question);
    if (!message) {
        if (context)
            free(context);
        return NULL;
    }
    response = ask_chatgpt(message, shell);
    free(message);
    if (context)
        free(context);
    free(baseprompt);
    return response;
}

void handle_chatgpt(input_state_t *state)
{
    char *message = get_chargpt_response(state->buffer, state->shell);

    if (message) {
        memset(state->buffer, 0, BUFFER_SIZE);
        strcpy(state->buffer, message);
        state->buffer_pos = strlen(message);
        state->cursor_pos = state->buffer_pos;
        free(message);
    }
    print_prompt(state);
}
