/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** get_prog_nb
*/

#include "../../include/corewar.h"

int get_prog_nb(stock_main_t *main_struct, char **argv, int pos)
{
    char *endptr;
    long prog_nb;

    prog_nb = strtol(argv[pos], &endptr, 10);
    if (*endptr != '\0' || prog_nb <= 0) {
        write(2, "./corewar: -n: invalid argument\n", 32);
        return 84;
    }
    main_struct->champ_info.pending_prog_nb = (int)prog_nb;
    return 0;
}
