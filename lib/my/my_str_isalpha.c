/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

int is_letter(char c)
{
    if (c >= 'a' && c <= 'z')
        return 1;
    if (c >= 'A' && c <= 'Z')
        return 1;
    return 0;
}

int my_str_isalpha(char const *str)
{
    if (str[0] == '\0')
        return 1;
    for (int i = 0; str[i] != '\0'; i++) {
        if (is_letter(str[i]) == 0)
            return 0;
    }
    return 1;
}
