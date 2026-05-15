/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** op_and
*/

#include "../../../include/corewar.h"

static int get_arg_val(stock_main_t *main_struct, process_t *process,
    int type, int offset)
{
    int arg = read_arg(main_struct->map, process->pc + offset, type, 0);

    if (type == 0x01)
        return (arg >= 1 && arg <= REG_NUMBER) ? process->reg[arg - 1] : 0;
    if (type == 0x03)
        return read_int_from_map(main_struct->map,
            (process->pc + arg % IDX_MOD) % MEM_SIZE);
    return arg;
}

void op_and(stock_main_t *main_struct, process_t *process)
{
    unsigned char coding = main_struct->map[(process->pc + 1) % MEM_SIZE];
    int type1 = (coding >> 6) & 0x03;
    int type2 = (coding >> 4) & 0x03;
    int off2 = 2 + get_arg_size(type1, 0);
    int off3 = off2 + get_arg_size(type2, 0);
    int arg1 = get_arg_val(main_struct, process, type1, 2);
    int arg2 = get_arg_val(main_struct, process, type2, off2);
    int reg_dest = main_struct->map[(process->pc + off3) % MEM_SIZE];
    int result = arg1 & arg2;

    if (reg_dest >= 1 && reg_dest <= REG_NUMBER)
        process->reg[reg_dest - 1] = result;
    process->carry = (result == 0) ? 1 : 0;
    process->pc = (process->pc + off3 + 1) % MEM_SIZE;
}
