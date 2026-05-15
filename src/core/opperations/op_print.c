/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** op_print
*/

#include "../../../include/corewar.h"

void op_print(stock_main_t *main_struct, process_t *process)
{
    int reg = main_struct->map[(process->pc + 1) % MEM_SIZE];
    char output;

    if (reg >= 1 && reg <= REG_NUMBER) {
        output = (char)(process->reg[reg - 1] % 256);
        write(1, &output, 1);
    }
    process->pc = (process->pc + 2) % MEM_SIZE;
}
