/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** loop
*/

#include "../../../include/corewar.h"

const process_call_t process_calls[] = {
    {op_live},
    {op_ld},
    {op_st},
    {op_add},
    {op_sub},
    {op_and},
    {op_or},
    {op_xor},
    {op_zjmp},
    {op_ldi},
    {op_sti},
    {op_fork},
    {op_lld},
    {op_lldi},
    {op_lfork},
    {op_print},
    {NULL}
};

void loop(stock_main_t *main_struct)
{
    process_t *current_process = NULL;
    unsigned char opcode = 0;

    for (node_t *temp = main_struct->processes;
        temp != NULL;
        temp = temp->next) {
        current_process = temp->data;
        opcode = main_struct->map[current_process->pc % MEM_SIZE];
        if (opcode >= 1 && opcode <= 16)
            process_calls[opcode - 1].func(main_struct, current_process);
        else
            current_process->pc = (current_process->pc + 1) % MEM_SIZE;
    }
}
