/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** my_perror
*/

#include "my.h"
#include "utils.h"
#include <errno.h>

/*
* This is the normal perror function, but it is modified to
* print a period ('.') at the end of the error message.
*/
void my_perror(const char *str)
{
    char *error_message = NULL;

    if (str == NULL)
        return;
    error_message = strerror(errno);
    write(STDERR_FILENO, str, my_strlen(str));
    write(STDERR_FILENO, ": ", 2);
    write(STDERR_FILENO, error_message, my_strlen(error_message));
    write(STDERR_FILENO, ".", 1);
    write(STDERR_FILENO, "\n", 1);
}
