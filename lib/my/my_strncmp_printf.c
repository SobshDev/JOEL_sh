/*
** EPITECH PROJECT, 2024
** Project Name
** File description:
** Project Description
*/

int my_strncmp_printf(char const *s1, char const *s2, int n)
{
    for (int i = 0; i < n; i++) {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
    }
    return 0;
}
