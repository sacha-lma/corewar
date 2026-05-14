/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** setup
*/

#include "../../include/corewar.h"

int setup(stock_main_t *main_struct)
{
    update_prog_nbr(main_struct);
    main_struct->champ_info.champions =
        merge_sort_lists(&main_struct->champ_info.champions, prog_sorter);
    if (champions_loader(main_struct) == 84)
        return 84;
    return 0;
}
