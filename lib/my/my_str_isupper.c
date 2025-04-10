/*
** EPITECH PROJECT, 2024
** day06
** File description:
** day06
*/

int is_upper(char c)
{
    if (c >= 'A' && c <= 'Z')
        return 1;
    return 0;
}

int my_str_isupper(char const *str)
{
    if (str[0] == '\0')
        return 1;
    for (int i = 0; str[i] != '\0'; i++) {
        if (is_upper(str[i]) == 0)
            return 0;
    }
    return 1;
}
