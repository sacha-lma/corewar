/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** read_arg — reads one instruction argument based on type and index flag
*/

#include "../../../include/corewar.h"

int read_arg(unsigned char *map, int pc, int type, int is_index)
{
    if (type == 0x01)
        return map[pc % MEM_SIZE];
    if (type == 0x02) {
        if (is_index) {
            return read_short_from_map(map, pc);
        } else {
            return read_int_from_map(map, pc);
        }
    }
    if (type == 0x03)
        return read_short_from_map(map, pc);
    return 0;
}
