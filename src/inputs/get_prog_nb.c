/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** get_prog_nb — parses the -n argument and stores the pending prog number
*/

#include "../../include/corewar.h"

static int parse_positive_int(const char *str, int *value)
{
    long long result = 0;

    if (str == NULL || *str == '\0')
        return 84;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 84;
        result = result * 10 + (str[i] - '0');
        if (result > 2147483647)
            return 84;
    }
    if (result <= 0)
        return 84;
    *value = (int)result;
    return 0;
}

int get_prog_nb(stock_main_t *main_struct, char **argv, int pos)
{
    int prog_nb;

    if (parse_positive_int(argv[pos], &prog_nb) == 84) {
        write(2, "./corewar: -n: invalid argument\n", 32);
        return 84;
    }
    main_struct->champ_info.pending_prog_nb = prog_nb;
    return 0;
}
