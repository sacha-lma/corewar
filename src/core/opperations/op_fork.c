/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** op_fork
*/

#include "../../../include/corewar.h"

void op_fork(stock_main_t *main_struct, process_t *process)
{
    short offset = (main_struct->map[(process->pc + 1) % MEM_SIZE] << 8) |
        (main_struct->map[(process->pc + 2) % MEM_SIZE]);
    int new_pc;
    process_t *child = malloc(sizeof(process_t));

    if (child == NULL)
        return;
    new_pc = (process->pc + (offset % IDX_MOD)) % MEM_SIZE;
    if (new_pc < 0)
        new_pc += MEM_SIZE;
    child->pc = new_pc;
    child->carry = process->carry;
    child->last_live = process->last_live;
    for (int i = 0; i < REG_NUMBER; i++)
        child->reg[i] = process->reg[i];
    push_back(&main_struct->processes, child);
    process->pc = (process->pc + 3) % MEM_SIZE;
}
