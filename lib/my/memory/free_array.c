/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** free_array
*/

#include <stdlib.h>

void free_array(char **array)
{
    if (array == NULL)
        return;
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}
