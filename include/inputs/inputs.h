/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** inputs
*/

#include "../corewar.h"

#ifndef INPUTS_H
    #define INPUTS_H
int manage_args(int argc, char **argv, stock_main_t *main_struct);
void get_prog_nb(stock_main_t *main_struct, char **argv, int pos);
void get_load_adress(stock_main_t *main_struct, char **argv, int pos);
void get_cycles(stock_main_t *main_struct, char **argv, int pos);
#endif
