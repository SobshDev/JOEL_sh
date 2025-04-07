/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

#include <stddef.h>
#include "my.h"

int compare_logic(char *str, char const *to_find, int i)
{
    if (str[i] == to_find[0]) {
        if (my_strncmp(&str[i], to_find, my_strlen(to_find)) == 0)
            return 1;
    }
    return 0;
}

char *my_strstr(char *str, char const *to_find)
{
    if (to_find[0] == '\0')
        return str;
    for (int i = 0; str[i] != '\0'; i++) {
        if (compare_logic(str, to_find, i) == 1)
            return &str[i];
    }
    return NULL;
}
