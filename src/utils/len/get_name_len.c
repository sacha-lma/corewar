/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** get_name_len
*/

#include "../../../include/corewar.h"

int get_name_len(char *name)
{
    int len = 0;

    for (; name[len] != '\0'; len++);
    for (; len > 0 && name[len - 1] == ' '; len--);
    return len;
}
