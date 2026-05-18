/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** main CSFML event loop — input, game step, rendering, winner screen
*/

#include <string.h>
#include "visu.h"

static void handle_key(visu_t *v, sfKeyCode key)
{
    switch (key) {
        case sfKeyQ:
        case sfKeyEscape:
            sfRenderWindow_close(v->window);
            break;
        case sfKeySpace:
            v->paused = !v->paused;
            break;
        case sfKeyN:
            if (v->paused)
                v->step = true;
            break;
        case sfKeyAdd:
        case sfKeyEqual:
            v->speed_ms -= SPEED_STEP;
            if (v->speed_ms < SPEED_MIN)
                v->speed_ms = SPEED_MIN;
            break;
        case sfKeySubtract:
        case sfKeyHyphen:
            v->speed_ms += SPEED_STEP;
            if (v->speed_ms > SPEED_MAX)
                v->speed_ms = SPEED_MAX;
            break;
        default:
            break;
    }
}

static void game_step(visu_t *v)
{
    visu_owner_step(v);
    call_op(v->core);
    v->core->nb_cycle++;
    if (v->core->nb_cycle >= (int)v->core->next_check_cycle) {
        check_deaths(v->core);
        v->core->next_check_cycle += v->core->cycle_to_die;
    }
}

static void render(visu_t *v)
{
    sfRenderWindow_clear(v->window, COL_BG);
    visu_draw_map(v);
    visu_draw_panel(v);
    visu_draw_status(v);
    sfRenderWindow_display(v->window);
}

static void show_winner(visu_t *v)
{
    char namebuf[21];
    int prog_nb = v->core->last_live_champion;
    champion_t *winner = NULL;
    sfRectangleShape *banner;
    sfText *t;
    char msg[256];
    int len;
    sfEvent event;

    for (node_t *n = v->core->champ_info.champions; n; n = n->next) {
        champion_t *c = n->data;
        if (c->prog_nb == prog_nb) {
            winner = c;
            break;
        }
    }
    render(v);
    banner = sfRectangleShape_create();
    sfRectangleShape_setSize(banner, (sfVector2f){(float)WIN_W, 70.0f});
    sfRectangleShape_setPosition(banner,
        (sfVector2f){0.0f, (float)(WIN_H / 2 - 35)});
    sfRectangleShape_setFillColor(banner, (sfColor){15, 60, 15, 230});
    sfRenderWindow_drawRectangleShape(v->window, banner, NULL);
    sfRectangleShape_destroy(banner);

    if (winner && v->font) {
        len = get_name_len(winner->header->prog_name);
        if (len > 20)
            len = 20;
        memcpy(namebuf, winner->header->prog_name, len);
        namebuf[len] = '\0';
        snprintf(msg, sizeof(msg),
            "VICTOIRE !  Le joueur %d (%s) a gagne !  [q] quitter",
            prog_nb, namebuf);
        t = sfText_create();
        sfText_setFont(t, v->font);
        sfText_setCharacterSize(t, 18);
        sfText_setFillColor(t, COL_LIVE);
        sfText_setPosition(t,
            (sfVector2f){20.0f, (float)(WIN_H / 2 - 12)});
        sfText_setString(t, msg);
        sfRenderWindow_drawText(v->window, t, NULL);
        sfText_destroy(t);
    }
    sfRenderWindow_display(v->window);

    while (sfRenderWindow_isOpen(v->window)) {
        while (sfRenderWindow_pollEvent(v->window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(v->window);
            if (event.type == sfEvtKeyPressed &&
                (event.key.code == sfKeyQ ||
                 event.key.code == sfKeyEscape))
                sfRenderWindow_close(v->window);
        }
    }
}

void visu_run(visu_t *v)
{
    sfEvent event;

    if (!v->window)
        return;
    while (sfRenderWindow_isOpen(v->window) &&
           v->core->processes != NULL) {
        while (sfRenderWindow_pollEvent(v->window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(v->window);
            if (event.type == sfEvtKeyPressed)
                handle_key(v, event.key.code);
        }
        if (!v->paused || v->step) {
            game_step(v);
            v->step = false;
        }
        render(v);
        if (!v->paused)
            sfSleep(sfMilliseconds(v->speed_ms));
        else
            sfSleep(sfMilliseconds(16));
    }
    if (v->core->processes == NULL && sfRenderWindow_isOpen(v->window))
        show_winner(v);
}
