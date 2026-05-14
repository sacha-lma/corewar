/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** loop
*/

#include "../../../include/corewar.h"

const process_call_t process_calls[] = {
    {NULL, NULL}
};

void loop(stock_main_t *main_struct)
{
    for (node_t *temp = main_struct->champ_info.champions;
        main_struct->champ_info.champion_count > 1
        && main_struct->nb_cycle != 0;
        temp = temp->next) {
        printf("champ = %s\n", ((champion_t *)temp->data)->header->prog_name);
        main_struct->champ_info.champion_count--;
    }
}
