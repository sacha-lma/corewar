/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** my_array_len — returns the length of a NULL-terminated pointer array
*/

#include "../../../include/corewar.h"

int my_array_len(char **array)
{
    int len = 0;

    if (array == NULL)
        return 0;
    for (; array[len] != NULL; len++);
    return len;
}
