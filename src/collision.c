/*
** EPITECH PROJECT, 2023
** myradar
** File description:
** The check_collision.c
*/

#include "../include/game.h"

static int compare_plane_collision(plane_t *plane1, plane_t *plane2,
    sfVector2f window_pos)
{
    if (rect_is_intersecting(get_plane_rect(plane1, window_pos),
    get_plane_rect(plane2, (sfVector2f){0, 0}))) {
        return 1;
    }
    return 0;
}

static int check_next_plane_collision(game_t *game,
    corner_t *corner, plane_list_t *plane1)
{
    int result = 0;

    for (plane_list_t *plane2 = plane1->next_plane;
        plane2 != NULL; plane2 = plane2->next_plane) {
        if (plane2->plane->is_alive == 2 ||
        verify_in_tower(game, corner, plane2->plane))
            continue;
        if (compare_plane_collision(plane1->plane, plane2->plane,
        (sfVector2f){0, 0})) {
            result = 1;
            plane2->plane->is_alive = 0;
        }
    }
    return result;
}

static int check_collision_in_corner(game_t *game, corner_t *corner,
    plane_list_t *plane1, sfVector2f window_pos)
{
    int result = 0;

    for (plane_list_t *plane2 = corner->plane_list;
    plane2 != NULL; plane2 = plane2->next_plane) {
        if (plane2->plane->is_alive == 2 ||
        verify_in_tower(game, corner, plane2->plane))
            continue;
        if (compare_plane_collision(plane1->plane, plane2->plane,
        window_pos)) {
            result = 1;
            plane2->plane->is_alive = 0;
        }
    }
    return result;
}

static int check_collision_in_query(game_t *game,
    corner_t *corner, plane_list_t *plane1)
{
    int result = 0;

    for (corner_t *corner2 = game->corner_list; corner2 != NULL;
        corner2 = corner2->next_corner) {
        if ((corner->area.top != corner2->area.top ||
        corner->area.left != corner2->area.left) &&
        corner->area.top - corner->area.height <= corner2->area.top &&
        corner->area.top + corner->area.height >= corner2->area.top &&
        corner->area.left - corner->area.width <= corner2->area.left &&
        corner->area.left + corner->area.width >= corner2->area.left)
            result = result + check_collision_in_corner(game, corner2,
            plane1, (sfVector2f){0, 0});
    }
    if (result > 0)
        result = 1;
    return result;
}

static void check_each_window_pos(game_t *game, corner_t *corner,
    plane_list_t *plane, int *result)
{
    if (rect_is_intersecting(corner->area,
    get_plane_rect(plane->plane, (sfVector2f){-1920, 0})))
        *result = *result + check_collision_in_corner(game, corner,
        plane, (sfVector2f){-1920, 0});
    if (rect_is_intersecting(corner->area,
    get_plane_rect(plane->plane, (sfVector2f){0, -1080})))
        *result = *result + check_collision_in_corner(game, corner,
        plane, (sfVector2f){0, -1080});
    if (rect_is_intersecting(corner->area,
    get_plane_rect(plane->plane, (sfVector2f){1920, 0})))
        *result = *result + check_collision_in_corner(game, corner,
        plane, (sfVector2f){1920, 0});
    if (rect_is_intersecting(corner->area,
    get_plane_rect(plane->plane, (sfVector2f){0, 1080})))
        *result = *result + check_collision_in_corner(game, corner,
        plane, (sfVector2f){0, 1080});
}

static int check_collision_in_query_border(game_t *game, plane_list_t *plane)
{
    int result = 0;

    for (corner_t *corner = game->corner_list; corner != NULL;
    corner = corner->next_corner)
        check_each_window_pos(game, corner, plane, &result);
    if (result > 0)
        result = 1;
    return result;
}

static void check_plane_collision(game_t *game, corner_t *corner)
{
    for (plane_list_t *plane1 = corner->plane_list;
    plane1 != NULL; plane1 = plane1->next_plane) {
        if (plane1->plane->is_alive == 2 ||
        verify_in_tower(game, corner, plane1->plane))
            continue;
        if (check_next_plane_collision(game, corner, plane1) ||
        check_collision_in_query(game, corner, plane1))
            plane1->plane->is_alive = 0;
        if (check_collision_in_query_border(game, plane1))
            plane1->plane->is_alive = 0;
    }
}

static void check_all_planes_in_a_tower(game_t *game, corner_t *corner)
{
    for (plane_list_t *plane = corner->plane_list; plane != NULL;
    plane = plane->next_plane) {
        verify_in_tower(game, corner, plane->plane);
    }
}

void check_collision(game_t *game)
{
    if (game->settings->pause == OFF) {
        for (corner_t *corner = game->corner_list; corner != NULL;
        corner = corner->next_corner)
            check_plane_collision(game, corner);
    } else {
        for (corner_t *corner = game->corner_list; corner != NULL;
        corner = corner->next_corner) {
            check_all_planes_in_a_tower(game, corner);
        }
    }
}
