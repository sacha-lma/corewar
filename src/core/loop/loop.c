/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** loop
*/

#include "../../../include/corewar.h"

static int count_alive_champions(stock_main_t *main_struct)
{
    int count = 0;
    int last_champ = -999;
    process_t *proc;

    for (node_t *temp = main_struct->processes; temp != NULL;
        temp = temp->next) {
        proc = temp->data;
        if (proc->champion_nb != last_champ) {
            count++;
            last_champ = proc->champion_nb;
        }
    }
    return count;
}

int loop(stock_main_t *main_struct)
{
    if (main_struct->processes == NULL) {
        dprintf(1, "The player %d has won!\n",
            main_struct->last_live_champion);
        return 84;
    }
    call_op(main_struct);
    main_struct->nb_cycle++;
    if (main_struct->nb_cycle > (int)main_struct->next_check_cycle) {
        check_deaths(main_struct);
        main_struct->next_check_cycle += main_struct->cycle_to_die;
        if (count_alive_champions(main_struct) <= 1) {
            dprintf(1, "The player %d has won!\n",
                main_struct->last_live_champion);
            return 84;
        }
    }
    return 0;
}
