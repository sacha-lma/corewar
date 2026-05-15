/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** set_process
*/

#include "../../../include/corewar.h"

int set_process(stock_main_t *main_struct, int load_add, champion_t *champion)
{
    process_t *process = malloc(sizeof(process_t));

    if (!process)
        return 84;
    process->pc = load_add;
    memset(process->reg, 0, REG_SIZE * REG_NUMBER);
    process->reg[0] = -champion->prog_nb;
    process->carry = false;
    process->last_live = 0;
    push_back(&main_struct->processes, process);
    return 0;
}
