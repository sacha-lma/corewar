/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** right info panel and bottom status bar
*/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "visu.h"

/* ── draw helpers ────────────────────────────────────────────────────────── */

static void draw_rect(visu_t *v, float x, float y, float w, float h,
    sfColor col)
{
    sfRectangleShape *r = sfRectangleShape_create();

    sfRectangleShape_setSize(r, (sfVector2f){w, h});
    sfRectangleShape_setPosition(r, (sfVector2f){x, y});
    sfRectangleShape_setFillColor(r, col);
    sfRenderWindow_drawRectangleShape(v->window, r, NULL);
    sfRectangleShape_destroy(r);
}

static void draw_text(visu_t *v, float x, float y, unsigned int sz,
    sfColor col, const char *fmt, ...)
{
    char buf[256];
    va_list ap;
    sfText *t;

    if (!v->font)
        return;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    t = sfText_create();
    sfText_setFont(t, v->font);
    sfText_setCharacterSize(t, sz);
    sfText_setFillColor(t, col);
    sfText_setPosition(t, (sfVector2f){x, y});
    sfText_setString(t, buf);
    sfRenderWindow_drawText(v->window, t, NULL);
    sfText_destroy(t);
}

static void section_header(visu_t *v, float y, const char *title)
{
    draw_rect(v, (float)PANEL_X, y, (float)PANEL_W, 16.0f, COL_HDR);
    draw_text(v, (float)PANEL_X + 4, y, (unsigned int)HDR_SIZE,
        COL_WHITE, "%s", title);
}

/* ── champion helpers ────────────────────────────────────────────────────── */

static int is_alive(visu_t *v, int prog_nb)
{
    for (node_t *n = v->core->processes; n; n = n->next)
        if (((process_t *)n->data)->champion_nb == prog_nb)
            return 1;
    return 0;
}

static int proc_count(visu_t *v, int prog_nb)
{
    int c = 0;

    for (node_t *n = v->core->processes; n; n = n->next)
        if (((process_t *)n->data)->champion_nb == prog_nb)
            c++;
    return c;
}

static const char *champ_name_short(champion_t *c, char buf[21])
{
    int len;

    if (!c->header) {
        buf[0] = '?';
        buf[1] = '\0';
        return buf;
    }
    len = get_name_len(c->header->prog_name);
    if (len > 20)
        len = 20;
    memcpy(buf, c->header->prog_name, len);
    buf[len] = '\0';
    return buf;
}

/* ── sections ────────────────────────────────────────────────────────────── */

static float draw_champions(visu_t *v, float y)
{
    char namebuf[21];
    champion_t *c;
    sfColor cc;
    int alive;

    section_header(v, y, " CHAMPIONS");
    y += 18.0f;
    for (node_t *n = v->core->champ_info.champions; n; n = n->next) {
        c = n->data;
        alive = is_alive(v, c->prog_nb);
        cc = champ_color(c->prog_nb);
        draw_rect(v, (float)PANEL_X, y, (float)PANEL_W, 15.0f, COL_PANEL);
        draw_text(v, (float)PANEL_X + 4, y, FONT_SIZE, cc,
            "[%d]", c->prog_nb);
        draw_text(v, (float)PANEL_X + 30, y, FONT_SIZE, COL_WHITE,
            "%-16s", champ_name_short(c, namebuf));
        if (alive)
            draw_text(v, (float)PANEL_X + 162, y, FONT_SIZE, COL_LIVE,
                "LIVE %dp", proc_count(v, c->prog_nb));
        else
            draw_text(v, (float)PANEL_X + 162, y, FONT_SIZE,
                COL_DEAD, "DEAD");
        y += 16.0f;
    }
    return y + 5.0f;
}

static float draw_info(visu_t *v, float y)
{
    section_header(v, y, " INFO");
    y += 18.0f;
    draw_text(v, (float)PANEL_X + 4, y, FONT_SIZE, COL_WHITE,
        "Cycle  : %d", v->core->nb_cycle);
    y += 14.0f;
    draw_text(v, (float)PANEL_X + 4, y, FONT_SIZE, COL_WHITE,
        "CTD    : %u", v->core->cycle_to_die);
    y += 14.0f;
    draw_text(v, (float)PANEL_X + 4, y, FONT_SIZE, COL_WHITE,
        "Speed  : %dms", v->speed_ms);
    y += 14.0f;
    draw_text(v, (float)PANEL_X + 4, y, FONT_SIZE,
        v->paused ? COL_DEAD : COL_LIVE,
        "Etat   : %s", v->paused ? "PAUSE" : "RUN");
    y += 18.0f;
    return y;
}

static float draw_controls(visu_t *v, float y)
{
    section_header(v, y, " CONTROLES");
    y += 18.0f;
    draw_text(v, (float)PANEL_X + 4, y, FONT_SIZE, COL_WHITE,
        "[ESPACE]    pause / run");
    y += 14.0f;
    draw_text(v, (float)PANEL_X + 4, y, FONT_SIZE, COL_WHITE,
        "[+/-]       vitesse (+/- = plus rapide)");
    y += 14.0f;
    draw_text(v, (float)PANEL_X + 4, y, FONT_SIZE, COL_WHITE,
        "[n]         step (pause seulement)");
    y += 14.0f;
    draw_text(v, (float)PANEL_X + 4, y, FONT_SIZE, COL_WHITE,
        "[q/ESC]     quitter");
    y += 18.0f;
    return y;
}

static void draw_legend(visu_t *v, float y)
{
    static const sfColor colors[] = {COL_C1, COL_C2, COL_C3, COL_C4};
    static const char *labels[] = {
        "Champion 1", "Champion 2", "Champion 3", "Champion 4"
    };
    int i;

    section_header(v, y, " LEGENDE");
    y += 18.0f;
    for (i = 0; i < 4; i++) {
        draw_rect(v, (float)PANEL_X + 4, y + 2, 10.0f, 10.0f, colors[i]);
        draw_text(v, (float)PANEL_X + 18, y, FONT_SIZE,
            COL_WHITE, "%s", labels[i]);
        y += 14.0f;
    }
    draw_rect(v, (float)PANEL_X + 4, y + 2, 10.0f, 10.0f, COL_PCDEF);
    draw_text(v, (float)PANEL_X + 18, y, FONT_SIZE, COL_WHITE, "@ = PC actif");
}

/* ── public ──────────────────────────────────────────────────────────────── */

void visu_draw_panel(visu_t *v)
{
    float y = 0.0f;

    draw_rect(v, (float)PANEL_X, 0, (float)PANEL_W, (float)MAP_H, COL_PANEL);
    draw_rect(v, (float)(MAP_W), 0, (float)SEP_W, (float)MAP_H, COL_SEP);
    y = draw_champions(v, y);
    y = draw_info(v, y);
    y = draw_controls(v, y);
    draw_legend(v, y);
}

void visu_draw_status(visu_t *v)
{
    draw_rect(v, 0.0f, (float)MAP_H, (float)WIN_W, (float)STAT_H, COL_STAT);
    draw_text(v, 8.0f, (float)MAP_H + 4, FONT_SIZE, COL_WHITE,
        "Cycle: %-8d  CTD: %-6u  Speed: %dms  %s",
        v->core->nb_cycle, v->core->cycle_to_die, v->speed_ms,
        v->paused ? "[ PAUSE ]" : "[ RUN ]");
    draw_text(v, 8.0f, (float)MAP_H + 20, FONT_SIZE,
        (sfColor){150, 150, 165, 255},
        "[ESPACE] pause  [+/-] vitesse  [n] step  [q/ESC] quitter"
        "  rouge=ch1  cyan=ch2  vert=ch3  jaune=ch4  @ = PC");
}
