/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** op_ld (0x02) — loads a direct or indirect value into a register
*/

#include "../../../include/corewar.h"

void op_ld(stock_main_t *main_struct, process_t *process)
{
    unsigned char coding = main_struct->map[(process->pc + 1) % MEM_SIZE];
    int type1 = coding >> 6 & 0x03;
    int arg1 = read_arg(main_struct->map, process->pc + 2, type1, 0);
    int reg = main_struct->map[(process->pc + 2 +
            get_arg_size(type1, 0)) % MEM_SIZE];

    if (type1 == 0x03)
        arg1 = read_int_from_map(main_struct->map,
            (process->pc + arg1 % IDX_MOD) % MEM_SIZE);
    if (reg >= 1 && reg <= REG_NUMBER)
        process->reg[reg - 1] = arg1;
    process->carry = (arg1 == 0) ? 1 : 0;
    process->pc = (process->pc + 3 + get_arg_size(type1, 0)) % MEM_SIZE;
}
