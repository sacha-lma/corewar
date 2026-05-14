/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** core
*/

#include "../corewar.h"

#ifndef CORE_H
    #define CORE_H
typedef struct champion_s {
    char *path;
    int prog_nb;
    int load_adress;
    header_t *header;
}champion_t;
typedef struct champ_info_s {
    node_t *champions;
    int pending_prog_nb;
    int pending_load_adress;
    int champion_count;
}champ_info_t;
typedef struct process_s {
    int pc;
    int reg[REG_NUMBER];
    bool carry;
    bool alive;
    int last_live;
}process_t;
typedef struct stock_maint_s {
    unsigned char map[MEM_SIZE];
    int nb_cycle;
    unsigned int cycle_to_die;
    champ_info_t champ_info;
    node_t *processes;
} stock_main_t;
typedef struct fcall_s {
    char *name;
    void (*func)(stock_main_t *, char **args, int pos);
}fcall_t;
typedef struct process_call_s {
    char *name;
    void (*func)(stock_main_t *);
} process_call_t;
#endif
