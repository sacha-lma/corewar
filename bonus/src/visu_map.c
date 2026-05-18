/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** renders the 6144-byte arena as a colored quad grid via sfVertexArray
*/

#include "visu.h"

sfColor champ_color(int prog_nb)
{
    static const sfColor palette[] = {COL_C1, COL_C2, COL_C3, COL_C4};

    if (prog_nb < 1)
        return COL_DEF;
    return palette[(prog_nb - 1) % 4];
}

sfColor pc_color(int prog_nb)
{
    static const sfColor palette[] = {COL_PC1, COL_PC2, COL_PC3, COL_PC4};

    if (prog_nb < 1)
        return COL_PCDEF;
    return palette[(prog_nb - 1) % 4];
}

static void build_pc_map(visu_t *v, unsigned char pc_map[MEM_SIZE])
{
    process_t *p;
    int addr;

    for (int i = 0; i < MEM_SIZE; i++)
        pc_map[i] = 0;
    for (node_t *n = v->core->processes; n; n = n->next) {
        p = n->data;
        addr = ((p->pc % MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
        pc_map[addr] = (unsigned char)p->champion_nb;
    }
}

static sfColor cell_color(visu_t *v, unsigned char pc_map[MEM_SIZE], int i)
{
    sfColor c;

    if (pc_map[i] > 0)
        return pc_color(pc_map[i]);
    if (v->owner[i] > 0) {
        c = champ_color(v->owner[i]);
        if (!v->core->map[i])
            c.a = 90;
        return c;
    }
    if (v->core->map[i])
        return COL_NZBG;
    return COL_BG;
}

static void set_quad(sfVertexArray *va, int i, float x, float y, sfColor col)
{
    sfVertex *vx;
    float x2 = x + (float)CELL_W - 1.0f;
    float y2 = y + (float)CELL_H - 1.0f;

    vx = sfVertexArray_getVertex(va, (sfUint32)(i * 4 + 0));
    vx->position = (sfVector2f){x, y};    vx->color = col;
    vx = sfVertexArray_getVertex(va, (sfUint32)(i * 4 + 1));
    vx->position = (sfVector2f){x2, y};   vx->color = col;
    vx = sfVertexArray_getVertex(va, (sfUint32)(i * 4 + 2));
    vx->position = (sfVector2f){x2, y2};  vx->color = col;
    vx = sfVertexArray_getVertex(va, (sfUint32)(i * 4 + 3));
    vx->position = (sfVector2f){x, y2};   vx->color = col;
}

void visu_draw_map(visu_t *v)
{
    unsigned char pc_map[MEM_SIZE];
    int col;
    int row;

    build_pc_map(v, pc_map);
    for (int i = 0; i < MEM_SIZE; i++) {
        col = i % MAP_COLS;
        row = i / MAP_COLS;
        set_quad(v->map_va, i,
            (float)(col * CELL_W),
            (float)(row * CELL_H),
            cell_color(v, pc_map, i));
    }
    sfRenderWindow_drawVertexArray(v->window, v->map_va, NULL);
}
