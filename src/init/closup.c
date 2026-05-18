/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** closup — frees all heap memory owned by stock_main_t
*/

#include "../../include/corewar.h"

static void free_champions(node_t **head)
{
    champion_t *champ;
    node_t *current = *head;
    node_t *temp;

    while (current != NULL) {
        champ = current->data;
        free(champ->header);
        free(champ);
        temp = current->next;
        free(current);
        current = temp;
    }
    *head = NULL;
}

static void free_processes(node_t **head)
{
    node_t *current = *head;
    node_t *temp;

    while (current != NULL) {
        free(current->data);
        temp = current->next;
        free(current);
        current = temp;
    }
    *head = NULL;
}

void closup(stock_main_t *main_struct)
{
    free_champions(&main_struct->champ_info.champions);
    free_processes(&main_struct->processes);
    free(main_struct);
}
