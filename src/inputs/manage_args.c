/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** manage_args
*/

#include "../../include/corewar.h"
#include <sys/stat.h>

const fcall_t fcalls[] = {
    {"-h", print_help},
    {"-help", print_help},
    {"-dump", get_cycles},
    {"-n", get_prog_nb},
    {"-a", get_load_adress},
    {NULL, NULL}
};

static int my_strlen_local(const char *str)
{
    int len = 0;

    if (str == NULL)
        return 0;
    while (str[len] != '\0')
        len++;
    return len;
}

static int my_strcmp_local(const char *left, const char *right)
{
    int i = 0;

    while (left[i] != '\0' && right[i] != '\0' && left[i] == right[i])
        i++;
    return (unsigned char)left[i] - (unsigned char)right[i];
}

static int needs_argument(const char *flag)
{
    if (my_strcmp_local(flag, "-h") == 0)
        return 0;
    if (my_strcmp_local(flag, "-help") == 0)
        return 0;
    return 1;
}

static int add_champion(int *i, char **argv, stock_main_t *main_struct)
{
    champion_t *champ;
    struct stat file_stat;
    int len = my_strlen_local(argv[*i]);

    if (lstat(argv[*i], &file_stat) != 0 || len < 4 ||
        my_strcmp_local(argv[*i] + len - 4, ".cor") != 0)
        return 84;
    champ = malloc(sizeof(champion_t));
    if (champ == NULL)
        return 84;
    champ->path = argv[*i];
    main_struct->champ_info.champion_count++;
    champ->prog_nb = main_struct->champ_info.pending_prog_nb;
    champ->load_adress = main_struct->champ_info.pending_load_adress;
    main_struct->champ_info.pending_prog_nb = -1;
    main_struct->champ_info.pending_load_adress = -1;
    push_back(&main_struct->champ_info.champions, champ);
    return 0;
}

static int call_func(int *i, int j, char **argv, stock_main_t *main_struct)
{
    int result;

    if (needs_argument(fcalls[j].name) == 1) {
        if (*i + 1 >= my_array_len(argv))
            return 84;
        result = fcalls[j].func(main_struct, argv, *i + 1);
    } else
        result = fcalls[j].func(main_struct, argv, *i);
    if (result == 84)
        return 84;
    if (result > 0)
        return result;
    if (needs_argument(fcalls[j].name) == 1)
        (*i)++;
    return 0;
}

static int is_flag(int *i, char **argv, stock_main_t *main_struct)
{
    for (int j = 0; fcalls[j].name != NULL; j++)
        if (my_strcmp_local(argv[*i], fcalls[j].name) == 0)
            return call_func(i, j, argv, main_struct);
    return add_champion(i, argv, main_struct);
}

int manage_args(const int argc, char **argv, stock_main_t *main_struct)
{
    int result;

    for (int i = 1; i < argc; i++) {
        result = is_flag(&i, argv, main_struct);
        if (result == 84)
            return 84;
        if (result > 0)
            return result;
    }
    return 0;
}
