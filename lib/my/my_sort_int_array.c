/*
** EPITECH PROJECT, 2024
** day04
** File description:
** day04
*/

#include "my.h"

int swapping_values(int *array, int j, int is_swapped)
{
    if (array[j] > array[j + 1]) {
        my_swap(&array[j], &array[j + 1]);
        is_swapped = 1;
    }
    return is_swapped;
}

void my_sort_int_array(int *array, int size)
{
    int is_swapped = 0;

    for (int i = 0; i < size - 1; i++) {
        is_swapped = 0;
        for (int j = 0; j < size - i - 1; j++) {
            is_swapped = swapping_values(array, j, is_swapped);
        }
        if (is_swapped == 0) {
            break;
        }
    }
}
