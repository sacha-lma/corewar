/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** op_zjmp
*/

#include "../../../include/corewar.h"

void op_zjmp(stock_main_t *main_struct, process_t *process)
{
    short arg = read_short_from_map(main_struct->map, process->pc + 1);

    if (process->carry == 1)
        process->pc = (process->pc + arg % IDX_MOD) % MEM_SIZE;
    else
        process->pc = (process->pc + OP_ZJMP_SIZE) % MEM_SIZE;
}
