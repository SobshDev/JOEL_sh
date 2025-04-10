/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

int is_lower(char c)
{
    if (c >= 'a' && c <= 'z')
        return 1;
    return 0;
}

int my_str_islower(char const *str)
{
    if (str[0] == '\0')
        return 1;
    for (int i = 0; str[i] != '\0'; i++) {
        if (is_lower(str[i]) == 0)
            return 0;
    }
    return 1;
}
