/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

#include "my.h"

int is_alphanumeric(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    if (c >= 'a' && c <= 'z')
        return 1;
    if (c >= 'A' && c <= 'Z')
        return 1;
    return 0;
}

char *my_strcapitalize_bis(char *str, int i)
{
    if (is_alphanumeric(str[i]) == 0) {
        if (str[i + 1] >= 'a' && str[i + 1] <= 'z')
            str[i + 1] = str[i + 1] - 32;
    }
    return str;
}

char *my_strcapitalize(char *str)
{
    str = my_strlowcase(str);
    if (str[0] >= 'a' && str[0] <= 'z')
        str[0] = str[0] - 32;
    for (int i = 0; str[i] != '\0'; i++) {
        str = my_strcapitalize_bis(str, i);
    }
    return str;
}
