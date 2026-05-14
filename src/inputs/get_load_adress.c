/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** get_load_adress
*/

#include "../../include/corewar.h"

void get_load_adress(stock_main_t *main_struct, char **argv, int pos)
{
    if (argv[pos] == NULL) {
        write(2, "./corewar: -a: missing argument\n", 32);
        exit(84);
    }
    main_struct->champ_info.pending_load_adress = atoi(argv[pos]);
}
