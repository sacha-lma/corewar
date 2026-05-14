/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** read_int_from_map
*/

#include "../../../include/corewar.h"

int read_int_from_map(unsigned char *map, int pc)
{
    unsigned int val = 0;

    val |= (unsigned int)map[(pc + 0) % MEM_SIZE] << 24;
    val |= (unsigned int)map[(pc + 1) % MEM_SIZE] << 16;
    val |= (unsigned int)map[(pc + 2) % MEM_SIZE] << 8;
    val |= (unsigned int)map[(pc + 3) % MEM_SIZE];
    return (int)val;
}
