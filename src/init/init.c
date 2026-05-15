/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** init
*/

#include "../../include/corewar.h"

void init(stock_main_t *main_struct)
{
    memset(main_struct->map, 0, MEM_SIZE);
    main_struct->nb_cycle = -1;
    main_struct->champ_info.champions = NULL;
    main_struct->champ_info.pending_prog_nb = -1;
    main_struct->champ_info.pending_load_adress = -1;
    main_struct->champ_info.champion_count = 0;
    main_struct->cycle_to_die = CYCLE_TO_DIE;
    main_struct->processes = NULL;
    main_struct->nb_live = 0;
    main_struct->next_check_cycle = CYCLE_TO_DIE;
}
