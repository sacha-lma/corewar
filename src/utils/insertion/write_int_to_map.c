/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** write_int_to_map
*/

#include "../../../include/corewar.h"

void write_int_to_map(unsigned char *map, int pc, int value)
{
    map[(pc + 0) % MEM_SIZE] = value >> 24 & 0xFF;
    map[(pc + 1) % MEM_SIZE] = value >> 16 & 0xFF;
    map[(pc + 2) % MEM_SIZE] = value >> 8 & 0xFF;
    map[(pc + 3) % MEM_SIZE] = value >> 0 & 0xFF;
}
