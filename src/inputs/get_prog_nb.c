/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** get_prog_nb
*/

#include "../../include/corewar.h"

void get_prog_nb(stock_main_t *main_struct, char **argv, int pos)
{
    int prog_nb;

    if (argv[pos] == NULL) {
        write(2, "./corewar: -n: missing argument\n", 32);
        exit(84);
    }
    prog_nb = atoi(argv[pos]);
    if (prog_nb <= 0) {
        write(2, "./corewar: -n: invalid argument\n", 32);
        exit(84);
    }
    main_struct->champ_info.pending_prog_nb = prog_nb;
}
