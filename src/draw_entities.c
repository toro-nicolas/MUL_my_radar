/*
** EPITECH PROJECT, 2023
** myradar
** File description:
** The draw.c
*/

#include "../include/game.h"

static void display_tower(game_t *game, tower_t *tower, sfVector2f window_pos)
{
    if (game->settings->sprites) {
        sfSprite_setPosition(game->display->tower, (sfVector2f){
        tower->position->x + window_pos.x, tower->position->y + window_pos.y});
        sfRenderWindow_drawSprite(game->window, game->display->tower, NULL);
    }
    if (game->settings->hitboxes) {
        sfCircleShape_setPosition(game->display->tower_shape, (sfVector2f){
        tower->position->x + window_pos.x, tower->position->y + window_pos.y});
        sfRenderWindow_drawCircleShape(game->window,
        game->display->tower_shape, NULL);
    }
}

void draw_towers(game_t *game)
{
    for (tower_t *tower = game->tower_list; tower != NULL;
    tower = tower->next) {
        sfCircleShape_setRadius(game->display->tower_shape, tower->radius);
        sfCircleShape_setOrigin(game->display->tower_shape,
        (sfVector2f){tower->radius, tower->radius});
        display_tower(game, tower, (sfVector2f){0, 0});
        display_tower(game, tower, (sfVector2f){-1920, 0});
        display_tower(game, tower, (sfVector2f){0, 1080});
        display_tower(game, tower, (sfVector2f){1920, 0});
        display_tower(game, tower, (sfVector2f){0, -1080});
    }
}

float get_angle(sfVector2f *pos1, sfVector2f *pos2)
{
    float x1 = pos1->x;
    float y1 = pos1->y;
    float x2 = pos2->x;
    float y2 = pos2->y;

    return atan2(y2 - y1, x2 - x1) * 180 / M_PI;
}

static void display_plane(game_t *game, plane_list_t *plane_list,
    sfVector2f windows_pos)
{
    if (game->settings->sprites) {
        sfSprite_setPosition(game->display->plane, (sfVector2f)
        {plane_list->plane->position->x + windows_pos.x,
        plane_list->plane->position->y + windows_pos.y});
        sfRenderWindow_drawSprite(game->window, game->display->plane, NULL);
    }
    if (game->settings->hitboxes) {
        sfRectangleShape_setPosition(game->display->plane_shape,
        (sfVector2f){plane_list->plane->position->x + windows_pos.x,
        plane_list->plane->position->y + windows_pos.y});
        sfRenderWindow_drawRectangleShape(game->window,
        game->display->plane_shape, NULL);
    }
}

static void display_planes(game_t *game, plane_list_t *plane_list)
{
    display_plane(game, plane_list, (sfVector2f){0, 0});
    display_plane(game, plane_list, (sfVector2f){-1920, 0});
    display_plane(game, plane_list, (sfVector2f){0, -1080});
    display_plane(game, plane_list, (sfVector2f){1920, 0});
    display_plane(game, plane_list, (sfVector2f){0, 1080});
}

static void set_entity_settings(game_t *game, plane_list_t *plane_list)
{
    sfRectangleShape_setOrigin(game->display->plane_shape,
    (sfVector2f){plane_list->plane->size / 2, plane_list->plane->size / 2});
    sfRectangleShape_setSize(game->display->plane_shape,
    (sfVector2f){plane_list->plane->size, plane_list->plane->size});
    sfSprite_setScale(game->display->plane, (sfVector2f)
    {plane_list->plane->size / 285.0, plane_list->plane->size / 268.0});
    sfSprite_setRotation(game->display->plane, get_angle
    (plane_list->plane->position, &(sfVector2f)
    {plane_list->plane->end_position->x + plane_list->plane->windows_pos.x,
    plane_list->plane->end_position->y + plane_list->plane->windows_pos.y}));
}

static void draw_all_planes_in_a_corner(game_t *game, corner_t *corner)
{
    for (plane_list_t *plane_list = corner->plane_list; plane_list != NULL;
    plane_list = plane_list->next_plane) {
        if (plane_list->plane->is_alive == 0)
            continue;
        if (plane_list->plane->is_alive == 2)
            sfRectangleShape_setOutlineColor
            (game->display->plane_shape, sfYellow);
        else
            sfRectangleShape_setOutlineColor
            (game->display->plane_shape, sfRed);
        set_entity_settings(game, plane_list);
        display_planes(game, plane_list);
    }
}

void draw_planes(game_t *game)
{
    for (corner_t *corner = game->corner_list; corner != NULL;
    corner = corner->next_corner) {
        draw_all_planes_in_a_corner(game, corner);
        destroy_all_planes_in_a_corner(corner);
    }
}
