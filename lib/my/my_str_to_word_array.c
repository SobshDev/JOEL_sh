/*
** EPITECH PROJECT, 2024
** day08
** File description:
** day08
*/

#include <stdlib.h>

int is_separator(char c, char const *sep)
{
    for (int i = 0; sep[i] != '\0'; i++) {
        if (c == sep[i])
            return 1;
    }
    return 0;
}

int *count_word_lengths(char const *str, char const *sep, int word_count)
{
    int *lengths = malloc(sizeof(int) * (word_count + 1));
    int word_index = 0;
    int word_length = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (!is_separator(str[i], sep)) {
            word_length += 1;
        }
        if (is_separator(str[i], sep) && word_length > 0) {
            lengths[word_index] = word_length;
            word_index += 1;
            word_length = 0;
        }
    }
    if (word_length > 0)
        lengths[word_index] = word_length;
    return lengths;
}

int count_words(char const *str, char const *sep)
{
    int total_words = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (!is_separator(str[i], sep) && (is_separator(str[i + 1], sep)
        || str[i + 1] == '\0'))
            total_words += 1;
    }
    return total_words;
}

void fill_in_data_of_array(char const *str, char const *sep, char **result)
{
    int word_index = 0;
    int letter_index = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (!is_separator(str[i], sep)) {
            result[word_index][letter_index] = str[i];
            letter_index += 1;
        }
        if (is_separator(str[i], sep) && letter_index > 0) {
            result[word_index][letter_index] = '\0';
            word_index += 1;
            letter_index = 0;
        }
    }
    if (letter_index > 0)
        result[word_index][letter_index] = '\0';
}

char **my_str_to_word_array(char const *str, char const *sep)
{
    int word_count = count_words(str, sep);
    int *word_lengths = count_word_lengths(str, sep, word_count);
    char **result = malloc(sizeof(char *) * (word_count + 1));

    for (int i = 0; i < word_count; i++) {
        result[i] = malloc(sizeof(char) * (word_lengths[i] + 1));
        result[i][0] = '\0';
    }
    fill_in_data_of_array(str, sep, result);
    result[word_count] = NULL;
    free(word_lengths);
    return result;
}
