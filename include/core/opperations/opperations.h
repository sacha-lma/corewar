/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** opperations
*/

#ifndef OPERATIONS_H
    #define OPERATIONS_H
    #include "core/core.h"
void op_live(stock_main_t *main_struct, process_t *process);
void op_ld(stock_main_t *main_struct, process_t *process);
void op_st(stock_main_t *main_struct, process_t *process);
void op_add(stock_main_t *main_struct, process_t *process);
void op_sub(stock_main_t *main_struct, process_t *process);
void op_and(stock_main_t *main_struct, process_t *process);
void op_or(stock_main_t *main_struct, process_t *process);
void op_xor(stock_main_t *main_struct, process_t *process);
void op_zjmp(stock_main_t *main_struct, process_t *process);
void op_ldi(stock_main_t *main_struct, process_t *process);
void op_sti(stock_main_t *main_struct, process_t *process);
void op_fork(stock_main_t *main_struct, process_t *process);
void op_lld(stock_main_t *main_struct, process_t *process);
void op_lldi(stock_main_t *main_struct, process_t *process);
void op_lfork(stock_main_t *main_struct, process_t *process);
void op_print(stock_main_t *main_struct, process_t *process);
#endif
