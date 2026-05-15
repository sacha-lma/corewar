/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** check_death
*/

#include "../../../include/corewar.h"

static void delete_process(stock_main_t *main_struct, int pos)
{
    process_t *process = get_at(main_struct->processes, pos);

    free(process);
    pop_at(&main_struct->processes, pos);
}

void check_deaths(stock_main_t *main_struct)
{
    int pos = 0;
    node_t *next;
    process_t *process = NULL;

    for (node_t *temp = main_struct->processes; temp; temp = next) {
        next = temp->next;
        process = temp->data;
        if (main_struct->nb_cycle - process->last_live >=
            (int)main_struct->cycle_to_die)
            delete_process(main_struct, pos);
        else
            pos++;
    }
    if (main_struct->nb_live >= NBR_LIVE) {
        if (main_struct->cycle_to_die > CYCLE_DELTA)
            main_struct->cycle_to_die -= CYCLE_DELTA;
        else
            main_struct->cycle_to_die = 1;
    }
    main_struct->nb_live = 0;
}
