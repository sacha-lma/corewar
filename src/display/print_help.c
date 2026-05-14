/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** print_help
*/

#include "../../include/corewar.h"

void print_help(stock_main_t *main_struct, char **argv, int pos)
{
    printf("USAGE\n");
    printf("./corewar [-dump nbr_cycle] [[-n prog_number] ");
    printf("[-a load_address] prog_name] ...\n");
    printf("DESCRIPTION\n");
    printf("-dump nbr_cycle dumps the state of the virtual machine\n");
    printf("after the nbr_cycle execution\n");
    printf("-n prog_number sets the next program's number. By\n");
    printf("default, the first free number in the parameter order\n");
    printf("-a load_address sets the next program's loading address.\n");
    printf("When no address is specified, optimize the addresses so\n");
    printf("that the processes are as far away from each other as\n");
    printf("possible. The addresses are MEM_SIZE modulo.\n");
    exit(0);
}
