/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** op_live
*/

#include "../../../include/corewar.h"

static void write_number(int value)
{
    char c;

    if (value < 0) {
        write(1, "-", 1);
        value = -value;
    }
    if (value >= 10)
        write_number(value / 10);
    c = (char)('0' + (value % 10));
    write(1, &c, 1);
}

static void print_alive_message(champion_t *champ)
{
    int name_len = get_name_len(champ->header->prog_name);

    write(1, "The player ", 11);
    write_number(champ->prog_nb);
    write(1, "(", 1);
    write(1, champ->header->prog_name, name_len);
    write(1, " )is alive.\n", 12);
}

void op_live(stock_main_t *main_struct, process_t *process)
{
    int champion_nb = read_int_from_map(main_struct->map, process->pc + 1);
    champion_t *champ = NULL;

    for (node_t *temp = main_struct->champ_info.champions; temp != NULL;
        temp = temp->next) {
        champ = temp->data;
        if (champ->prog_nb == -champion_nb) {
            print_alive_message(champ);
            main_struct->nb_live++;
            process->last_live = main_struct->nb_cycle;
            main_struct->last_live_champion = champ->prog_nb;
            break;
        }
    }
    process->pc = (process->pc + OP_LIVE_SIZE) % MEM_SIZE;
}
