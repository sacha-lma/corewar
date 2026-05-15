/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** loop
*/

#include "../../../include/corewar.h"

int loop(stock_main_t *main_struct)
{
    if (main_struct->processes == NULL)
        return 84;
    call_op(main_struct);
    main_struct->nb_cycle++;
    if (main_struct->nb_cycle >= (int)main_struct->next_check_cycle) {
        check_deaths(main_struct);
        main_struct->next_check_cycle += main_struct->cycle_to_die;
    }
    return 0;
}
