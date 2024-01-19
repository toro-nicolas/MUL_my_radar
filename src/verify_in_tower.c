/*
** EPITECH PROJECT, 2024
** myradar
** File description:
** The verify_in_tower.c
*/

#include "../include/game.h"

static int check_other_circle(plane_t *plane, tower_list_t *tower)
{
    if (rect_is_intersecting_circle(get_plane_rect(plane,
    (sfVector2f){0, -1080}), (sfVector2f){tower->tower->position->x +
    tower->window_pos.x, tower->tower->position->y + tower->window_pos.y},
    tower->tower->radius))
        return 1;
    if (rect_is_intersecting_circle(get_plane_rect(plane,
    (sfVector2f){1920, 0}), (sfVector2f){tower->tower->position->x +
    tower->window_pos.x, tower->tower->position->y + tower->window_pos.y},
    tower->tower->radius))
        return 1;
    if (rect_is_intersecting_circle(get_plane_rect(plane,
    (sfVector2f){0, 1080}), (sfVector2f){tower->tower->position->x +
    tower->window_pos.x, tower->tower->position->y + tower->window_pos.y},
    tower->tower->radius))
        return 1;
    return 0;
}

static int change_protected(plane_t *plane)
{
    plane->is_alive = 2;
    return 1;
}

int check_in_tower(corner_t *corner, plane_t *plane)
{
    for (tower_list_t *tower = corner->tower_list; tower != NULL;
    tower = tower->next_tower) {
        if (rect_is_intersecting_circle(get_plane_rect(plane, (sfVector2f)
        {0, 0}), (sfVector2f){tower->tower->position->x + tower->window_pos.x,
        tower->tower->position->y + tower->window_pos.y},
        tower->tower->radius))
            return change_protected(plane);
        if (rect_is_intersecting_circle(get_plane_rect(plane,
        (sfVector2f){-1920, 0}), (sfVector2f){tower->tower->position->x +
        tower->window_pos.x, tower->tower->position->y + tower->window_pos.y},
        tower->tower->radius))
            return change_protected(plane);
        if (check_other_circle(plane, tower))
            return change_protected(plane);
    }
    return 0;
}

int verify_in_tower(game_t *game, corner_t *corner, plane_t *plane)
{
    if (check_in_tower(corner, plane))
        return 1;
    for (corner_t *corner2 = game->corner_list; corner2 != NULL;
    corner2 = corner2->next_corner) {
        if ((corner->area.top != corner2->area.top ||
        corner->area.left != corner2->area.left) &&
        corner->area.top - corner->area.height <= corner2->area.top &&
        corner->area.top + corner->area.height >= corner2->area.top &&
        corner->area.left - corner->area.width <= corner2->area.left &&
        corner->area.left + corner->area.width >= corner2->area.left &&
        check_in_tower(corner2, plane))
            return 1;
    }
    return 0;
}
