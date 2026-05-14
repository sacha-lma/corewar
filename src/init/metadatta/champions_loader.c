/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** champions_loader
*/

#include "../../../include/corewar.h"

void champions_loader(stock_main_t *main)
{
    int fd = 0;
    int load_add = 0;
    champion_t *champion = NULL;

    for (int i = 0; i < main->champ_info.champion_count; i++) {
        champion = get_at(main->champ_info.champions, i + 1);
        load_add = MEM_SIZE / main->champ_info.champion_count * i;
        if (champion->load_adress != -1)
            load_add = champion->load_adress % MEM_SIZE;
        fd = open(champion->path, O_RDONLY);
        read(fd, champion->header, sizeof(header_t));
        read(fd, main->map + load_add,
            __builtin_bswap32(champion->header->prog_size));
        set_process(main, load_add, champion);
        close(fd);
    }
}
