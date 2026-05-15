/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** op_sti
*/

#include "../../../include/corewar.h"

static void get_args(stock_main_t *main_struct, process_t *process,
    int *args, int *types)
{
    unsigned char coding = main_struct->map[(process->pc + 1) % MEM_SIZE];
    int offset = process->pc + 2;

    types[0] = (coding >> 6) & 0x03;
    types[1] = (coding >> 4) & 0x03;
    types[2] = (coding >> 2) & 0x03;
    args[0] = read_arg(main_struct->map, offset,
        types[0], 0);
    args[1] = read_arg(main_struct->map,
        offset + get_arg_size(types[0], 0), types[1], 1);
    args[2] = read_arg(main_struct->map,
        offset + get_arg_size(types[0], 0) +
        get_arg_size(types[1], 1), types[2], 1);
}

void op_sti(stock_main_t *main_struct, process_t *process)
{
    int args[3] = {0};
    int types[3] = {0};
    int addr = 0;

    get_args(main_struct, process, args, types);
    if (types[1] == 0x01)
        args[1] = process->reg[args[1] - 1];
    if (types[2] == 0x01)
        args[2] = process->reg[args[2] - 1];
    addr = (args[1] + args[2]) % IDX_MOD;
    write_int_to_map(main_struct->map,
        (process->pc + addr) % MEM_SIZE,
        process->reg[args[0] - 1]);
    process->pc = (process->pc + 2 + get_arg_size(types[0], 0)
        + get_arg_size(types[1], 1) + get_arg_size(types[2],
            1)) % MEM_SIZE;
}
