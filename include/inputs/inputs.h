/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** argument-parsing function declarations
*/

#ifndef INPUTS_H
    #define INPUTS_H
    #include "core/core.h"
int manage_args(int argc, char **argv, stock_main_t *main_struct);
int get_prog_nb(stock_main_t *main_struct, char **argv, int pos);
int get_load_adress(stock_main_t *main_struct, char **argv, int pos);
int get_cycles(stock_main_t *main_struct, char **argv, int pos);
#endif
