/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** manage_args
*/

#include "../../include/corewar.h"

const fcall_t fcalls[] = {
    {"-h", print_help},
    {"-help", print_help},
    {"-dump", get_cycles},
    {"-n", get_prog_nb},
    {"-a", get_load_adress},
    {NULL, NULL}
};

static int add_champion(int *i, char **argv, stock_main_t *main)
{
    champion_t *champ;

    if (access(argv[*i], F_OK) != 0 || strstr(argv[*i], ".cor") == NULL)
        return 84;
    champ = malloc(sizeof(champion_t));
    if (champ == NULL)
        return 84;
    champ->path = argv[*i];
    main->champion_count++;
    champ->prog_nb = main->pending_prog_nb == -1
        ? -1 : (unsigned int)main->pending_prog_nb;
    champ->load_adress = main->pending_load_adress;
    main->pending_prog_nb = -1;
    main->pending_load_adress = -1;
    push_back(&main->champions, champ);
    return 0;
}

static int is_flag(int *i, char **argv, stock_main_t *main)
{
    for (int j = 0; fcalls[j].name != NULL; j++) {
        if (strcmp(argv[*i], fcalls[j].name) == 0) {
            fcalls[j].func(main, argv, *i + 1);
            (*i)++;
            return 0;
        }
    }
    return add_champion(i, argv, main);
}

int manage_args(const int argc, char **argv, stock_main_t *main)
{
    for (int i = 1; i < argc; i++)
        if (is_flag(&i, argv, main) == 84)
            return 84;
    return 0;
}
