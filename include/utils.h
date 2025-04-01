/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** utils
*/

#ifndef UTILS_H_
    #define UTILS_H_

    #include "font.h"
    #define UNDERLINE "\033[4m"
    #define BOLD "\033[1m"

    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <ctype.h>


// Forward declaration
typedef enum token_type_e token_type_t;

bool is_whitespace(char c);
bool is_char_in_str(char c, char const *chars);
char *my_strndup(char const *src, int n);
void *my_realloc(void *ptr, size_t old_size, size_t new_size);
char *run_backtick_command(const char *cmd);
bool is_token_redirect(token_type_t type);
void my_perror(const char *str);
char *my_itoa(int value);
bool is_directory(char *path);
bool file_exists(char *path);
bool is_valid_var_name(char *name);

#endif /* !UTILS_H_ */
