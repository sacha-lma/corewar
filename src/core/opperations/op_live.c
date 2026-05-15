/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** op_live
*/

#include "../../../include/corewar.h"

void op_live(stock_main_t *main_struct, process_t *process)
{
    int champion_nb = read_int_from_map(main_struct->map, process->pc + 1);
    champion_t *champ = NULL;

    for (node_t *temp = main_struct->champ_info.champions; temp != NULL;
        temp = temp->next) {
        champ = temp->data;
        if (champ->prog_nb == -champion_nb) {
            dprintf(1, "The player %d(%s) is alive.\n",
                champ->prog_nb, champ->header->prog_name);
            main_struct->nb_live++;
            process->last_live = main_struct->nb_cycle;
            main_struct->last_live_champion = champ->prog_nb;
            break;
        }
    }
    process->pc = (process->pc + OP_LIVE_SIZE) % MEM_SIZE;
}
