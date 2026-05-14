/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** set_process
*/

#include "../../../include/corewar.h"

void set_process(stock_main_t *main, int load_add, champion_t *champion)
{
    process_t *process = malloc(sizeof(process_t));

    process->pc = load_add;
    memset(process->reg, 0, REG_SIZE);
    process->reg[0] = -champion->prog_nb;
    process->carry = false;
    process->alive = true;
    process->last_live = 0;
    push_back(&main->processes, process);
}
