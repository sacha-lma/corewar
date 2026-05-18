/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** corewar_visu entry point — init core, start CSFML visualizer
*/

#include "visu.h"

static int init_core(visu_t *v, int argc, char **argv)
{
    int arg_status;

    v->core = malloc(sizeof(stock_main_t));
    if (!v->core)
        return 84;
    init(v->core);
    arg_status = manage_args(argc, argv, v->core);
    if (arg_status == 84) {
        closup(v->core);
        return 84;
    }
    if (arg_status > 0) {
        closup(v->core);
        return 1;
    }
    if (setup(v->core) == 84) {
        closup(v->core);
        return 84;
    }
    return 0;
}

int main(int argc, char **argv)
{
    visu_t v = {0};
    int rc;

    v.speed_ms = SPEED_DEF;
    rc = init_core(&v, argc, argv);
    if (rc != 0)
        return rc == 1 ? 0 : 84;
    visu_owner_build(&v);
    visu_init(&v);
    if (!v.window) {
        closup(v.core);
        return 84;
    }
    visu_run(&v);
    visu_cleanup(&v);
    closup(v.core);
    return 0;
}
