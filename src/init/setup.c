/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** setup
*/

#include "../../include/corewar.h"

int setup(stock_main_t *main)
{
    int fd = 0;
    int load_add = 0;
    champion_t *champion = NULL;

    update_prog_nbr(main);
    main->champ_info.champions =
        merge_sort_lists(&main->champ_info.champions, prog_sorter);
    for (int i = 0; i < main->champ_info.champion_count; i++) {
        champion = get_at(main->champ_info.champions, i + 1);
        load_add = MEM_SIZE / main->champ_info.champion_count * i;
        if (champion->load_adress != -1)
            load_add = champion->load_adress % MEM_SIZE;
        fd = open(champion->path, O_RDONLY);
        read(fd, champion->header, sizeof(header_t));
        read(fd, main->map + load_add,
            __builtin_bswap32(champion->header->prog_size));
        close(fd);
    }
    return 0;
}
