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

static void print_winner(stock_main_t *main_struct)
{
    champion_t *champ = NULL;

    for (node_t *temp = main_struct->champ_info.champions; temp != NULL;
        temp = temp->next) {
        champ = temp->data;
        if (champ->prog_nb == main_struct->last_live_champion) {
            dprintf(1, "The player %d(%.*s)has won.\n",
                champ->prog_nb,
                get_name_len(champ->header->prog_name),
                champ->header->prog_name);
            return;
        }
    }
}

static void update_cycle_to_die(stock_main_t *main_struct)
{
    if (main_struct->cycle_to_die > CYCLE_DELTA)
        main_struct->cycle_to_die -= CYCLE_DELTA;
    else
        main_struct->cycle_to_die = 1;
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
    update_cycle_to_die(main_struct);
    main_struct->nb_live = 0;
    if (main_struct->processes == NULL)
        print_winner(main_struct);
}
