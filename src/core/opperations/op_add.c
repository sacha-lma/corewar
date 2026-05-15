/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** op_add
*/

#include "../../../include/corewar.h"

void op_add(stock_main_t *main_struct, process_t *process)
{
    int reg1 = main_struct->map[(process->pc + 2) % MEM_SIZE];
    int reg2 = main_struct->map[(process->pc + 3) % MEM_SIZE];
    int reg_fin = main_struct->map[(process->pc + 4) % MEM_SIZE];

    if (reg1 >= 1 && reg1 <= REG_NUMBER &&
        reg2 >= 1 && reg2 <= REG_NUMBER &&
        reg_fin >= 1 && reg_fin <= REG_NUMBER) {
        process->reg[reg_fin - 1] = process->reg[reg1 - 1] +
            process->reg[reg2 - 1];
        if (process->reg[reg_fin - 1] == 0)
            process->carry = true;
        else
            process->carry = false;
    }
    process->pc = (process->pc + 5) % MEM_SIZE;
}
