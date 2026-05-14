/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** loop
*/

#include "../../../include/corewar.h"

const process_call_t process_calls[] = {
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
