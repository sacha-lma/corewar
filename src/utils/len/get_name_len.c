/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** get_name_len
*/

#include "../../../include/corewar.h"

int get_name_len(char *name)
{
    int len = (int)strlen(name);

    while (len > 0 && name[len - 1] == ' ')
        len--;
    return len;
}
