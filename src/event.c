/*
** EPITECH PROJECT, 2023
** myradar
** File description:
** The event.c
*/

#include "../include/game.h"

static void change_settings_state(bool_t *settings)
{
    *settings = !*settings;
}

static void change_music_state(game_t *game)
{
    if (game->settings->music == ON) {
        sfMusic_pause(game->display->music);
        game->settings->music = OFF;
    } else {
        sfMusic_play(game->display->music);
        game->settings->music = ON;
    }
}

static void check_arrow_pressed(game_t *game, sfEvent event)
{
    if (event.key.code == sfKeyUp)
        return sfRenderWindow_setFramerateLimit(game->window, 120);
    if (event.key.code == sfKeyDown)
        return sfRenderWindow_setFramerateLimit(game->window, 30);
    if (event.key.code == sfKeyLeft && game->settings->game_speed > 1) {
        game->settings->game_speed = game->settings->game_speed / 2;
        return;
    }
    if (event.key.code == sfKeyRight && game->settings->game_speed < 1024) {
        game->settings->game_speed = game->settings->game_speed * 2;
        return;
    }
}

static void check_key_pressed(game_t *game, sfEvent event)
{
    if (event.key.code == sfKeyL)
        return change_settings_state(&game->settings->hitboxes);
    if (event.key.code == sfKeyS)
        return change_settings_state(&game->settings->sprites);
    if (event.key.code == sfKeySpace)
        return change_settings_state(&game->settings->pause);
    if (event.key.code == sfKeyTab)
        return change_settings_state(&game->settings->panel);
    if (event.key.code == sfKeyF)
        return change_settings_state(&game->settings->fps);
    if (event.key.code == sfKeyT)
        return change_settings_state(&game->settings->time);
    if (event.key.code == sfKeyC)
        return change_settings_state(&game->settings->corners);
    if (event.key.code == sfKeyP)
        return change_music_state(game);
    return check_arrow_pressed(game, event);
}

static void manage_mouse_click(sfMouseButtonEvent event)
{
    my_printf("Mouse x=%d y=%d\n", event.x, event.y);
}

static void close_window(sfRenderWindow *window)
{
    sfRenderWindow_close(window);
}

void analyse_events(game_t *game, sfEvent event)
{
    if (event.type == sfEvtClosed)
        return close_window(game->window);
    if (event.type == sfEvtMouseButtonPressed)
        return manage_mouse_click(event.mouseButton);
    if (event.type == sfEvtKeyReleased)
        return check_key_pressed(game, event);
}
