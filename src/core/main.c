/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** main
*/

#include "../../include/corewar.h"

int main(int argc, char **argv)
{
    stock_main_t *main = malloc(sizeof(stock_main_t));

    if (main == NULL)
        return 84;
    init(main);
    if (manage_args(argc, argv, main) == 84) {
        free(main);
        return 84;
    }
    setup(main);
    free(main);
    return 0;
}
