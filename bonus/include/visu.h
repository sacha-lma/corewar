/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** CSFML visualiser — types, constants, and function declarations
*/

#ifndef VISU_H
# define VISU_H
# include <SFML/Graphics.h>
# include <stdbool.h>
# include "corewar.h"

/* ── layout ─────────────────────────────────────────────────────────────── */
# define CELL_W     8
# define CELL_H     14
# define MAP_COLS   128
# define MAP_ROWS   (MEM_SIZE / MAP_COLS)   /* 48  */
# define MAP_W      (MAP_COLS * CELL_W)     /* 1024 */
# define MAP_H      (MAP_ROWS * CELL_H)     /* 672  */
# define SEP_W      6
# define PANEL_X    (MAP_W + SEP_W)         /* 1030 */
# define PANEL_W    368
# define WIN_W      (PANEL_X + PANEL_W)     /* 1398 */
# define STAT_H     58
# define WIN_H      (MAP_H + STAT_H)        /* 730  */
# define FONT_SIZE  11
# define HDR_SIZE   12

/* ── speed ──────────────────────────────────────────────────────────────── */
# define SPEED_DEF  30
# define SPEED_MIN  1
# define SPEED_MAX  500
# define SPEED_STEP 5

/* ── colors ─────────────────────────────────────────────────────────────── */
# define COL_C1    ((sfColor){210,  60,  60, 255})
# define COL_C2    ((sfColor){ 60, 195, 195, 255})
# define COL_C3    ((sfColor){ 60, 185,  60, 255})
# define COL_C4    ((sfColor){205, 185,  50, 255})
# define COL_PC1   ((sfColor){255, 130, 130, 255})
# define COL_PC2   ((sfColor){130, 255, 255, 255})
# define COL_PC3   ((sfColor){130, 255, 130, 255})
# define COL_PC4   ((sfColor){255, 255, 130, 255})
# define COL_PCDEF ((sfColor){255, 255, 255, 255})
# define COL_DEF   ((sfColor){ 80,  80,  80, 255})
# define COL_BG    ((sfColor){ 12,  12,  18, 255})
# define COL_NZBG  ((sfColor){ 55,  55,  65, 255})
# define COL_PANEL ((sfColor){ 22,  22,  30, 255})
# define COL_HDR   ((sfColor){ 35,  70, 140, 255})
# define COL_WHITE ((sfColor){230, 230, 230, 255})
# define COL_LIVE  ((sfColor){ 60, 220,  60, 255})
# define COL_DEAD  ((sfColor){200,  60,  60, 255})
# define COL_STAT  ((sfColor){ 18,  18,  30, 255})
# define COL_SEP   ((sfColor){ 40,  40,  55, 255})

typedef struct s_visu {
    stock_main_t    *core;
    sfRenderWindow  *window;
    sfFont          *font;
    sfVertexArray   *map_va;
    int              speed_ms;
    bool             paused;
    bool             step;
    unsigned char    owner[MEM_SIZE];
} visu_t;

/* visu_map.c (also defines color helpers used by visu_panel.c) */
sfColor champ_color(int prog_nb);
sfColor pc_color(int prog_nb);

/* visu_init.c */
void visu_init(visu_t *v);
void visu_owner_build(visu_t *v);
void visu_owner_step(visu_t *v);
void visu_cleanup(visu_t *v);

/* visu_map.c */
void visu_draw_map(visu_t *v);

/* visu_panel.c */
void visu_draw_panel(visu_t *v);
void visu_draw_status(visu_t *v);

/* visu_loop.c */
void visu_run(visu_t *v);

#endif
