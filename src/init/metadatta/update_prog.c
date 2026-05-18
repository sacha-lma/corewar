/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** update_prog_nbr — auto-assigns prog numbers to unset champions
*/

#include "../../../include/corewar.h"

static int is_taken(stock_main_t *main_struct, int nb)
{
    champion_t *champion = NULL;

    for (node_t *temp = main_struct->champ_info.champions; temp != NULL;
        temp = temp->next) {
        champion = temp->data;
        if (champion->prog_nb != -1 && champion->prog_nb == nb)
            return 1;
    }
    return 0;
}

static void change_prog(stock_main_t *main_struct, champion_t *champion,
    int *index)
{
    if (champion->prog_nb == -1) {
        while (is_taken(main_struct, *index))
            (*index)++;
        champion->prog_nb = *index;
        (*index)++;
    }
}

void update_prog_nbr(stock_main_t *main_struct)
{
    champion_t *champion = NULL;
    int index = 1;

    for (node_t *temp = main_struct->champ_info.champions; temp != NULL;
        temp = temp->next) {
        champion = temp->data;
        change_prog(main_struct, champion, &index);
    }
}
