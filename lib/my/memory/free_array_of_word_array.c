/*
** EPITECH PROJECT, 2026
** minishel_2
** File description:
** free_array_of_word_array
*/

#include "../../Headers/my.h"
#include <stdlib.h>

void free_array_of_word_arrays(char ***arr)
{
    for (int i = 0; arr && arr[i]; i++) {
        if (arr[i])
            free_array(arr[i]);
    }
    free(arr);
}
