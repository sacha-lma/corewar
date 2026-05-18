/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** op_lfork (0x0F) — long fork: new process at pc + offset (no IDX_MOD)
*/

#include "../../../include/corewar.h"

void op_lfork(stock_main_t *main_struct, process_t *process)
{
    short arg = read_short_from_map(main_struct->map, process->pc + 1);
    process_t *new_proc = malloc(sizeof(process_t));

    if (!new_proc)
        return;
    *new_proc = *process;
    new_proc->pc = (process->pc + arg) % MEM_SIZE;
    push_back(&main_struct->processes, new_proc);
    process->pc = (process->pc + OP_LFORK_SIZE) % MEM_SIZE;
}
