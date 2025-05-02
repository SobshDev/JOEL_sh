/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** my_str_replace
*/

#include "my.h"

static int count_occurrences(char *str, const char *old, int len_old)
{
    int count = 0;
    char *pos = str;
    char *found = my_strstr(pos, old);

    while (found != NULL) {
        count++;
        pos = found + len_old;
        found = my_strstr(pos, old);
    }
    return count;
}

static int calculate_result_size(char *str, int count, int len_old,
    int len_new)
{
    return my_strlen(str) + (len_new - len_old) * count + 1;
}

static char *copy_segment(char *dest, char *src, int len)
{
    my_strncpy(dest, src, len);
    return dest + len;
}

static char *process_replacements(char *result, char *str, const char *old,
    const char *new)
{
    int len_old = my_strlen(old);
    int len_new = my_strlen(new);
    int count = count_occurrences(str, old, len_old);
    char *dest = result;
    char *found;
    int len_front;

    while (count > 0) {
        found = my_strstr(str, old);
        len_front = found - str;
        dest = copy_segment(dest, str, len_front);
        dest = my_strcpy(dest, new) + len_new;
        str = found + len_old;
        count--;
    }
    my_strcpy(dest, str);
    return result;
}

char *my_str_replace(char *str, const char *old, const char *new)
{
    char *result;
    int len_old;
    int len_new;
    int count;

    if (!str || !old || !new)
        return NULL;
    len_old = my_strlen(old);
    if (len_old == 0)
        return my_strdup(str);
    len_new = my_strlen(new);
    count = count_occurrences(str, old, len_old);
    result = malloc(calculate_result_size(str, count, len_old, len_new));
    if (!result)
        return NULL;
    return process_replacements(result, str, old, new);
}
