/*
** EPITECH PROJECT, 2024
** day04
** File description:
** day04
*/

int my_strlen(char const *str)
{
    int i = 0;

    for (i = 0; str[i] != '\0'; i++);
    return i;
}
