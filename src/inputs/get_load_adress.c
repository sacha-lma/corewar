/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** get_load_adress
*/

#include "../../include/corewar.h"

static int parse_int(const char *str, int *value)
{
    long result = 0;
    int sign = 1;
    int i = 0;

    if (str == NULL || str[0] == '\0')
        return 84;
    if (str[i] == '+' || str[i] == '-') {
        sign = (str[i] == '-') ? -1 : 1;
        i++;
    }
    if (str[i] == '\0')
        return 84;
    for (; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 84;
        result = result * 10 + (str[i] - '0');
    }
    *value = (int)(result * sign);
    return 0;
}

int get_load_adress(stock_main_t *main_struct, char **argv, int pos)
{
    int addr;

    if (parse_int(argv[pos], &addr) == 84) {
        write(2, "./corewar: -a: invalid argument\n", 32);
        return 84;
    }
    main_struct->champ_info.pending_load_adress = addr;
    return 0;
}
