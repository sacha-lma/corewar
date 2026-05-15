/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** main
*/

#include "../../include/corewar.h"

static int run_corewar(stock_main_t *main_struct, int argc, char **argv)
{
    int arg_status = manage_args(argc, argv, main_struct);

    if (arg_status == 84)
        return 84;
    if (arg_status > 0)
        return 0;
    if (setup(main_struct) == 84)
        return 84;
    while (loop(main_struct) == 0);
    return 0;
}

int main(int argc, char **argv)
{
    stock_main_t *main_struct = malloc(sizeof(stock_main_t));
    int status;

    if (main_struct == NULL)
        return 84;
    init(main_struct);
    status = run_corewar(main_struct, argc, argv);
    closup(main_struct);
    return status;
}
