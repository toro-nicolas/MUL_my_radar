/*
** EPITECH PROJECT, 2023
** myradar
** File description:
** The update_corner.c
*/

#include "../include/game.h"

static void add_plane_in_corner(game_t *game, corner_t *corner, plane_t *plane)
{
    plane_list_t *new_list = malloc(sizeof(plane_list_t));

    new_list->plane = plane;
    if (corner->plane_list == NULL)
        new_list->next_plane = NULL;
    else
        new_list->next_plane = corner->plane_list;
    corner->plane_list = new_list;
}

static void check_plane_in_corner(game_t *game, plane_t *plane)
{
    for (corner_t *corner = game->corner_list; corner != NULL;
    corner = corner->next_corner) {
        if (vector_is_in_rect(*plane->position, corner->area)) {
            add_plane_in_corner(game, corner, plane);
            break;
        }
    }
}

void update_corner(game_t *game)
{
    for (plane_t *plane = game->plane_list; plane != NULL;
    plane = plane->next) {
        if (plane->delay == 0)
            check_plane_in_corner(game, plane);
    }
}
