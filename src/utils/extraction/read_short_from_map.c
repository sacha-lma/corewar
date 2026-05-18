/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** read_short_from_map — big-endian 16-bit read with wrap-around
*/

#include "../../../include/corewar.h"

short read_short_from_map(unsigned char *map, int pc)
{
    short val = 0;

    val |= map[(pc + 0) % MEM_SIZE] << 8;
    val |= map[(pc + 1) % MEM_SIZE];
    return val;
}
