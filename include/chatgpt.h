/*
** EPITECH PROJECT, 2025
** B-PSU-200-MPL-2-1-42sh-louis.bagnol
** File description:
** chatgpt
*/

#ifndef INCLUDED_CHATGPT_H
    #define INCLUDED_CHATGPT_H

typedef struct shell_s shell_t;

char *run_command(char *command);
char *get_context(void);
char *ask_chatgpt(char *message, shell_t *shell);

#endif
