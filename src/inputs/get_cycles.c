/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** get_cycles
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

int get_cycles(stock_main_t *main_struct, char **argv, int pos)
{
    int cycles;

    if (parse_positive_int(argv[pos], &cycles) == 84) {
        write(2, "./corewar: -dump: invalid argument\n", 35);
        return 84;
    }
    main_struct->nb_cycle = cycles;
    return 0;
}
