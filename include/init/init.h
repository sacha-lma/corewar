/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** init
*/

#ifndef INIT_H
    #define INIT_H
    #include "../corewar.h"
void init(stock_main_t *main_struct);
int setup(stock_main_t *main_struct_struct);
void update_prog_nbr(stock_main_t *main_struct);
int prog_sorter(void *a, void *b);
int champions_loader(stock_main_t *main_struct);
int set_process(stock_main_t *main_struct, int load_add, champion_t *champion);
#endif
