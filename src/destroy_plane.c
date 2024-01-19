/*
** EPITECH PROJECT, 2023
** myradar
** File description:
** The destroy_plane.c
*/

#include "../include/game.h"

void destroy_plane(game_t *game,
    plane_t **previous_plane, plane_t **current_plane)
{
    if (previous_plane == NULL || (*previous_plane) == NULL)
        *(&game->plane_list) = (*current_plane)->next;
    else
        (*previous_plane)->next = (*current_plane)->next;
    free((*current_plane)->position);
    free((*current_plane)->end_position);
    free((*current_plane)->direction);
    free((*current_plane));
    if (previous_plane == NULL || (*previous_plane) == NULL)
        (*current_plane) = *(&game->plane_list);
    else
        (*current_plane) = (*previous_plane)->next;
}

void destroy_plane_in_plane_list(plane_list_t **plane_list,
    plane_list_t **previous_plane, plane_list_t **current_plane)
{
    if ((*previous_plane) == NULL)
        (*plane_list) = (*current_plane)->next_plane;
    else
        (*previous_plane)->next_plane = (*current_plane)->next_plane;
    free((*current_plane));
    if ((*previous_plane) == NULL)
        (*current_plane) = *(plane_list);
    else
        (*current_plane) = (*previous_plane)->next_plane;
}

static int compare_sign(int a, int b)
{
    if (a < 0 && b < 0)
        return -1;
    if (a > 0 && b > 0)
        return 1;
    return 0;
}

void check_plane_arrived(game_t *game)
{
    plane_t *current_plane = *(&game->plane_list);
    plane_t *previous_plane = NULL;
    static int nb = 1;

    while (current_plane != NULL) {
        if (current_plane->is_alive == 0 ||
        ((compare_sign(current_plane->direction->x,
        current_plane->end_position->x + current_plane->windows_pos.x -
        current_plane->position->x) == 0 &&
        compare_sign(current_plane->direction->y,
        current_plane->end_position->y + current_plane->windows_pos.y -
        current_plane->position->y) == 0))) {
            destroy_plane(game, &previous_plane, &current_plane);
        } else {
            current_plane->is_alive = 1;
            previous_plane = current_plane;
            current_plane = current_plane->next;
        }
    }
}

void destroy_all_planes_in_a_corner(corner_t *corner)
{
    plane_list_t *tmp;

    while (corner->plane_list != NULL) {
        tmp = corner->plane_list;
        corner->plane_list = corner->plane_list->next_plane;
        free(tmp);
    }
}
