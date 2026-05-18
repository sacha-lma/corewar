/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** CSFML window creation, font loading, owner-map builder
*/

#include <string.h>
#include "visu.h"

static const char *font_paths[] = {
    "/usr/share/fonts/truetype/liberation/LiberationMono-Regular.ttf",
    "/usr/share/fonts/truetype/jetbrains-mono/JetBrainsMono-Regular.ttf",
    "/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf",
    "/usr/share/fonts/truetype/noto/NotoMono-Regular.ttf",
    "/usr/share/fonts/truetype/freefont/FreeMono.ttf",
    NULL
};

static sfFont *load_font(void)
{
    sfFont *font;
    int i;

    for (i = 0; font_paths[i]; i++) {
        font = sfFont_createFromFile(font_paths[i]);
        if (font)
            return font;
    }
    return NULL;
}

void visu_init(visu_t *v)
{
    sfVideoMode mode = {WIN_W, WIN_H, 32};
    sfContextSettings settings = {0};

    v->window = sfRenderWindow_create(mode, "Corewar Visualizer",
        sfClose, &settings);
    if (!v->window)
        return;
    sfRenderWindow_setFramerateLimit(v->window, 60);
    v->font = load_font();
    v->map_va = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(v->map_va, sfQuads);
    sfVertexArray_resize(v->map_va, (sfUint32)(MEM_SIZE * 4));
}

void visu_owner_build(visu_t *v)
{
    champion_t *c;
    int sz;
    int i;

    memset(v->owner, 0, MEM_SIZE);
    for (node_t *n = v->core->champ_info.champions; n; n = n->next) {
        c = n->data;
        if (!c->header)
            continue;
        sz = (int)__builtin_bswap32((unsigned int)c->header->prog_size);
        for (i = 0; i < sz; i++)
            v->owner[(c->load_adress + i) % MEM_SIZE] =
                (unsigned char)c->prog_nb;
    }
}

static void owner_mark(visu_t *v, int addr, int champ_nb)
{
    for (int i = 0; i < 4; i++)
        v->owner[((addr + i) % MEM_SIZE + MEM_SIZE) % MEM_SIZE] =
            (unsigned char)champ_nb;
}

static void pre_step_st(visu_t *v, process_t *p)
{
    unsigned char *map = v->core->map;
    int pc = p->pc;
    unsigned char coding = map[(pc + 1) % MEM_SIZE];
    int type2 = (coding >> 4) & 0x03;
    int reg_src = map[(pc + 2) % MEM_SIZE];
    int arg2;
    int addr;

    if (type2 != 0x03 || reg_src < 1 || reg_src > REG_NUMBER)
        return;
    arg2 = read_arg(map, pc + 3, type2, 0);
    addr = ((pc + arg2 % IDX_MOD) % MEM_SIZE + MEM_SIZE) % MEM_SIZE;
    owner_mark(v, addr, p->champion_nb);
}

static void pre_step_sti(visu_t *v, process_t *p)
{
    unsigned char *map = v->core->map;
    int pc = p->pc;
    unsigned char coding = map[(pc + 1) % MEM_SIZE];
    int types[3];
    int args[3];
    int sz0;
    int sz1;
    int addr;

    types[0] = (coding >> 6) & 0x03;
    types[1] = (coding >> 4) & 0x03;
    types[2] = (coding >> 2) & 0x03;
    sz0 = get_arg_size(types[0], 0);
    sz1 = get_arg_size(types[1], 1);
    args[0] = read_arg(map, pc + 2, types[0], 0);
    args[1] = read_arg(map, pc + 2 + sz0, types[1], 1);
    args[2] = read_arg(map, pc + 2 + sz0 + sz1, types[2], 1);
    if (types[1] == 0x01) {
        if (args[1] < 1 || args[1] > REG_NUMBER)
            return;
        args[1] = p->reg[args[1] - 1];
    }
    if (types[2] == 0x01) {
        if (args[2] < 1 || args[2] > REG_NUMBER)
            return;
        args[2] = p->reg[args[2] - 1];
    }
    addr = ((pc + (args[1] + args[2]) % IDX_MOD) % MEM_SIZE + MEM_SIZE)
        % MEM_SIZE;
    owner_mark(v, addr, p->champion_nb);
}

void visu_owner_step(visu_t *v)
{
    process_t *p;
    unsigned char op;

    for (node_t *n = v->core->processes; n; n = n->next) {
        p = n->data;
        op = v->core->map[p->pc % MEM_SIZE];
        if (op == 0x03)
            pre_step_st(v, p);
        else if (op == 0x0B)
            pre_step_sti(v, p);
    }
}

void visu_cleanup(visu_t *v)
{
    if (v->map_va)
        sfVertexArray_destroy(v->map_va);
    if (v->font)
        sfFont_destroy(v->font);
    if (v->window)
        sfRenderWindow_destroy(v->window);
}
