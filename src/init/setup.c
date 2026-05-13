/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** setup
*/

#include "../../include/corewar.h"

int setup(stock_main_t *main)
{
    update_prog_nbr(main);
    main->champ_info.champions =
        merge_sort_lists(&main->champ_info.champions, prog_sorter);
    return 0;
}
