/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** get_cycles
*/

#include "../../include/corewar.h"

int get_cycles(stock_main_t *main_struct, char **argv, int pos)
{
    char *endptr;
    long cycles;

    cycles = strtol(argv[pos], &endptr, 10);
    if (*endptr != '\0' || cycles <= 0) {
        write(2, "./corewar: -dump: invalid argument\n", 35);
        return 84;
    }
    main_struct->nb_cycle = (int)cycles;
    return 0;
}
