/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** get_arg_size — returns the byte size of an argument by type and index flag
*/

#include "../../../include/corewar.h"

int get_arg_size(int type, int is_index)
{
    if (type == 0x01)
        return 1;
    if (type == 0x02)
        return is_index ? 2 : 4;
    if (type == 0x03)
        return 2;
    return 0;
}
