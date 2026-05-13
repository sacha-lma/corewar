/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** prog_sorter
*/

#include "../../../include/corewar.h"

int prog_sorter(void *a, void *b)
{
    node_t *node_a = a;
    node_t *node_b = b;
    champion_t *champ_a = node_a->data;
    champion_t *champ_b = node_b->data;

    if (champ_a->prog_nb < champ_b->prog_nb)
        return 1;
    return 0;
}
