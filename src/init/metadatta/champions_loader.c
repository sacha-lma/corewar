/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** champions_loader
*/

#include "../../../include/corewar.h"

static int read_binary(int fd, champion_t *champion, stock_main_t *main_struct,
    int load_add)
{
    if (!champion->header)
        return 84;
    if (read(fd, champion->header, sizeof(header_t)) != sizeof(header_t))
        return 84;
    if (read(fd, main_struct->map + load_add,
            __builtin_bswap32(champion->header->prog_size)) !=
        __builtin_bswap32(champion->header->prog_size))
        return 84;
    return 0;
}

static int get_load_add(champion_t *champion, int count, int i)
{
    if (champion->load_adress != -1)
        return champion->load_adress % MEM_SIZE;
    return MEM_SIZE / count * i;
}

static int load_one(stock_main_t *main_struct, champion_t *champion, int i)
{
    int fd;
    int load_add;
    int count = main_struct->champ_info.champion_count;

    load_add = get_load_add(champion, count, i);
    champion->load_adress = load_add;
    fd = open(champion->path, O_RDONLY);
    if (fd == -1)
        return 84;
    champion->header = malloc(sizeof(header_t));
    if (read_binary(fd, champion, main_struct, load_add) == 84) {
        close(fd);
        return 84;
    }
    close(fd);
    return set_process(main_struct, load_add, champion);
}

int champions_loader(stock_main_t *main_struct)
{
    champion_t *champion = NULL;

    for (int i = 0; i < main_struct->champ_info.champion_count; i++) {
        champion = get_at(main_struct->champ_info.champions, i);
        if (load_one(main_struct, champion, i) == 84)
            return 84;
    }
    return 0;
}
