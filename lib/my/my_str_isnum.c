/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

int is_num(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    return 0;
}

int my_str_isnum(char const *str)
{
    if (str[0] == '\0')
        return 1;
    for (int i = 0; str[i] != '\0'; i++) {
        if (is_num(str[i]) == 0)
            return 0;
    }
    return 1;
}
