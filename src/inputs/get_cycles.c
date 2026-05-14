/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** get_cycles
*/

#include "../../include/corewar.h"

void get_cycles(stock_main_t *main_struct, char **argv, int pos)
{
    int cycles;

    if (argv[pos] == NULL) {
        write(2, "./corewar: -dump: missing argument\n", 35);
        exit(84);
    }
    cycles = atoi(argv[pos]);
    if (cycles <= 0) {
        write(2, "./corewar: -dump: invalid argument\n", 35);
        exit(84);
    }
    main_struct->nb_cycle = (unsigned int)cycles;
}
