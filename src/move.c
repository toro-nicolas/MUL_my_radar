/*
** EPITECH PROJECT, 2023
** myradar
** File description:
** The move.c
*/

#include "../include/game.h"

static void check_border(plane_t *plane)
{
    if (plane->windows_pos.x == 0 && plane->windows_pos.y == 0)
        return;
    if (plane->position->x < 0) {
        plane->position->x = 1920;
        plane->windows_pos = (sfVector2f){0, 0};
    }
    if (plane->position->x > 1920) {
        plane->position->x = 0;
        plane->windows_pos = (sfVector2f){0, 0};
    }
    if (plane->position->y < 0) {
        plane->position->y = 1080;
        plane->windows_pos = (sfVector2f){0, 0};
    }
    if (plane->position->y > 1080) {
        plane->position->y = 0;
        plane->windows_pos = (sfVector2f){0, 0};
    }
}

static void update_plane_position(game_t *game, plane_t *plane)
{
    plane->position->x += (plane->direction->x * (plane->speed *
    game->time_between_frames)) * game->settings->game_speed;
    plane->position->y += (plane->direction->y * (plane->speed *
    game->time_between_frames)) * game->settings->game_speed;
    check_border(plane);
}

static void update_plane_place(game_t *game)
{
    for (plane_t *plane = game->plane_list; plane != NULL;
    plane = plane->next) {
        if (plane->is_alive == 0)
            continue;
        if (plane->delay != 0 && (float)plane->delay <=
        (float)(sfClock_getElapsedTime(game->game_time).microseconds /
        1000000.0)) {
            plane->delay = 0;
            continue;
        }
        if (plane->delay != 0)
            continue;
        update_plane_position(game, plane);
    }
}

void move_plane(game_t *game)
{
    if (game->settings->pause == OFF)
        update_plane_place(game);
}
