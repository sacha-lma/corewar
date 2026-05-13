/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** setup
*/

#include "../../include/corewar.h"

int setup(stock_main_t *main)
{
    champion_t *champion = NULL;

    update_prog_nbr(main);
    main->champ_info.champions =
        merge_sort_lists(&main->champ_info.champions, prog_sorter);
    for (node_t *current = main->champ_info.champions; current != NULL;
        current = current->next) {
        champion = current->data;
        printf("champ prog = %d\n", champion->prog_nb);
    }
    return 0;
}
