/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** main
*/

#include "../../include/corewar.h"

int main(int argc, char **argv)
{
    stock_main_t *main_struct = malloc(sizeof(stock_main_t));

    if (main_struct == NULL)
        return 84;
    init(main_struct);
    if (manage_args(argc, argv, main_struct) == 84) {
        closup(main_struct);
        return 84;
    }
    if (setup(main_struct) == 84) {
        closup(main_struct);
        return 84;
    }
    loop(main_struct);
    closup(main_struct);
    return 0;
}
