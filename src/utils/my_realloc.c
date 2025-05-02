/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** my_realloc
*/

#include "utils.h"

void *my_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void *new_ptr = malloc(new_size);
    size_t copy_size = 0;

    if (!new_ptr)
        return NULL;
    if (!ptr)
        return new_ptr;
    if (new_size < old_size)
        copy_size = new_size;
    else
        copy_size = old_size;
    for (size_t i = 0; i < copy_size; i++)
        ((char *)new_ptr)[i] = ((char *)ptr)[i];
    free(ptr);
    return new_ptr;
}
