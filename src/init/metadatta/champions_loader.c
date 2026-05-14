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

int champions_loader(stock_main_t *main_struct)
{
    int fd = 0;
    int load_add = 0;
    champion_t *champion = NULL;

    for (int i = 0; i < main_struct->champ_info.champion_count; i++) {
        champion = get_at(main_struct->champ_info.champions, i);
        load_add = MEM_SIZE / main_struct->champ_info.champion_count * i;
        if (champion->load_adress != -1)
            load_add = champion->load_adress % MEM_SIZE;
        champion->load_adress = load_add;
        fd = open(champion->path, O_RDONLY);
        if (fd == -1)
            return 84;
        champion->header = malloc(sizeof(header_t));
        read_binary(fd, champion, main_struct, load_add);
        if (set_process(main_struct, load_add, champion) == 84)
            return 84;
        close(fd);
    }
    return 0;
}
