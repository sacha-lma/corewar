/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** init
*/

#include "../../include/corewar.h"

void init(stock_main_t *main)
{
    memset(main->map, 0, MEM_SIZE);
    main->nb_cycle = 0;
    main->champ_info.champions = NULL;
    main->champ_info.pending_prog_nb = -1;
    main->champ_info.pending_load_adress = -1;
    main->champ_info.champion_count = 0;
    main->cycle_to_die = CYCLE_TO_DIE;
}
