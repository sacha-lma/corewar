/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** get_load_adress
*/

#include "../../include/corewar.h"

void get_load_adress(stock_main_t *main, char **argv, int pos)
{
    if (argv[pos] == NULL) {
        write(2, "./corewar: -a: missing argument\n", 32);
        exit(84);
    }
    main->pending_load_adress = atoi(argv[pos]);
}
