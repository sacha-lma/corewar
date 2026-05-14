/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** get_load_adress
*/

#include "../../include/corewar.h"

int get_load_adress(stock_main_t *main_struct, char **argv, int pos)
{
    char *endptr;
    long addr;

    addr = strtol(argv[pos], &endptr, 10);
    if (*endptr != '\0') {
        write(2, "./corewar: -a: invalid argument\n", 32);
        return 84;
    }
    main_struct->champ_info.pending_load_adress = (int)addr;
    return 0;
}
