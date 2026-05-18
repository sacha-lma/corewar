/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** kills processes below the live threshold, prints the winner
*/

#include "../../../include/corewar.h"

static void write_number(int value)
{
    char c;

    if (value < 0) {
        write(1, "-", 1);
        value = -value;
    }
    if (value >= 10)
        write_number(value / 10);
    c = (char)('0' + (value % 10));
    write(1, &c, 1);
}

static void delete_process(stock_main_t *main_struct, int pos)
{
    process_t *process = get_at(main_struct->processes, pos);

    free(process);
    pop_at(&main_struct->processes, pos);
}

static void print_winner(stock_main_t *main_struct)
{
    champion_t *champ = NULL;
    int name_len;

    for (node_t *temp = main_struct->champ_info.champions; temp != NULL;
        temp = temp->next) {
        champ = temp->data;
        if (champ->prog_nb == main_struct->last_live_champion) {
            name_len = get_name_len(champ->header->prog_name);
            write(1, "The player ", 11);
            write_number(champ->prog_nb);
            write(1, "(", 1);
            write(1, champ->header->prog_name, name_len);
            write(1, ")has won.\n", 10);
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
