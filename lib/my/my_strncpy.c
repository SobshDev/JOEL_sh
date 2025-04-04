/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    for (i = 0; i < n; i++) {
        dest[i] = src[i];
    }
    return dest;
}
