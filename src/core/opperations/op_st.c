/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** op_st
*/

#include "../../../include/corewar.h"

void op_st(stock_main_t *main_struct, process_t *process)
{
    unsigned char coding = main_struct->map[(process->pc + 1) % MEM_SIZE];
    int type2 = (coding >> 4) & 0x03;
    int reg_src = main_struct->map[(process->pc + 2) % MEM_SIZE];
    int arg2 = read_arg(main_struct->map, process->pc + 3, type2, 0);

    if (type2 == 0x01 && reg_src >= 1 && reg_src <= REG_NUMBER &&
        arg2 >= 1 && arg2 <= REG_NUMBER)
        process->reg[arg2 - 1] = process->reg[reg_src - 1];
    if (type2 == 0x03 && reg_src >= 1 && reg_src <= REG_NUMBER)
        write_int_to_map(main_struct->map,
            (process->pc + arg2 % IDX_MOD) % MEM_SIZE,
            process->reg[reg_src - 1]);
    process->pc = (process->pc + 3 + get_arg_size(type2, 0)) % MEM_SIZE;
}
