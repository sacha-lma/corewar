/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** print_help — prints usage and flag descriptions to stdout
*/

#include "../../include/corewar.h"

static void print_usage(void)
{
    write(1, "USAGE\n", 6);
    write(1, "./corewar [-dump nbr_cycle] [[-n prog_number]", 45);
    write(1, " [-a load_address] prog_name] ...\n", 34);
}

static void print_desc(void)
{
    write(1, "DESCRIPTION\n", 12);
    write(1, "-dump nbr_cycle dumps the state of the virtual machine", 54);
    write(1, " after the nbr_cycle execution\n", 31);
    write(1, "-n prog_number sets the next program's number. By", 49);
    write(1, " default, the first free number in the parameter order\n", 55);
    write(1, "-a load_address sets the next program's loading address.\n", 57);
    write(1, "When no address is specified, optimize the addresses so\n", 56);
    write(1, "that the processes are as far away from each other as\n", 54);
    write(1, "possible. The addresses are MEM_SIZE modulo.\n", 45);
}

int print_help(stock_main_t *main_struct, char **argv, int pos)
{
    (void)main_struct;
    (void)argv;
    (void)pos;
    print_usage();
    print_desc();
    return 1;
}
