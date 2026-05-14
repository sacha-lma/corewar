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

static int add_champion(int *i, char **argv, stock_main_t *main_struct)
{
    champion_t *champ;

    if (access(argv[*i], F_OK) != 0 || strstr(argv[*i], ".cor") == NULL)
        return 84;
    champ = malloc(sizeof(champion_t));
    if (champ == NULL)
        return 84;
    champ->path = argv[*i];
    main_struct->champ_info.champion_count++;
    champ->prog_nb = main_struct->champ_info.pending_prog_nb == -1
        ? -1 : (unsigned int)main_struct->champ_info.pending_prog_nb;
    champ->load_adress = main_struct->champ_info.pending_load_adress;
    main_struct->champ_info.pending_prog_nb = -1;
    main_struct->champ_info.pending_load_adress = -1;
    push_back(&main_struct->champ_info.champions, champ);
    return 0;
}

static int call_func(int *i, int j, char **argv, stock_main_t *main_struct)
{
    if (*i + 1 >= my_array_len(argv))
        return 84;
    fcalls[j].func(main_struct, argv, *i + 1);
    (*i)++;
    return 0;
}

static int is_flag(int *i, char **argv, stock_main_t *main_struct)
{
    for (int j = 0; fcalls[j].name != NULL; j++)
        if (strcmp(argv[*i], fcalls[j].name) == 0)
            return call_func(i, j, argv, main_struct);
    return add_champion(i, argv, main_struct);
}

int manage_args(const int argc, char **argv, stock_main_t *main_struct)
{
    for (int i = 1; i < argc; i++)
        if (is_flag(&i, argv, main_struct) == 84)
            return 84;
    return 0;
}
