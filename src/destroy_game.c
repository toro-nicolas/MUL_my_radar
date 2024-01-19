/*
** EPITECH PROJECT, 2023
** myradar
** File description:
** The destroy_game.c
*/

#include "../include/game.h"

static void destroy_game_display(game_t *game)
{
    sfRectangleShape_destroy(game->display->corner_shape);
    sfRectangleShape_destroy(game->display->plane_shape);
    sfCircleShape_destroy(game->display->tower_shape);
    sfTexture_destroy(game->display->texture);
    sfSprite_destroy(game->display->background);
    sfSprite_destroy(game->display->tower);
    sfSprite_destroy(game->display->plane);
    sfText_destroy(game->display->game_text);
    sfFont_destroy(game->display->game_font);
    sfMusic_destroy(game->display->music);
    free(game->display);
}

static void destroy_planes(game_t *game)
{
    plane_t *tmp;

    while (game->plane_list != NULL) {
        tmp = game->plane_list;
        game->plane_list = game->plane_list->next;
        free(tmp->position);
        free(tmp->end_position);
        free(tmp->direction);
        free(tmp);
    }
}

static void destroy_corner(game_t *game)
{
    corner_t *tmp;
    tower_list_t *tower_tmp;

    while (game->corner_list != NULL) {
        tmp = game->corner_list;
        game->corner_list = game->corner_list->next_corner;
        destroy_all_planes_in_a_corner(tmp);
        while (tmp->tower_list != NULL) {
            tower_tmp = tmp->tower_list;
            tmp->tower_list = tmp->tower_list->next_tower;
            free(tower_tmp);
        }
        free(tmp);
    }
}

static void destroy_towers(game_t *game)
{
    tower_t *tmp;

    while (game->tower_list != NULL) {
        tmp = game->tower_list;
        game->tower_list = game->tower_list->next;
        free(tmp->position);
        free(tmp);
    }
}

void destroy_game(game_t *game)
{
    sfClock_destroy(game->frames_clock);
    destroy_game_display(game);
    destroy_planes(game);
    destroy_corner(game);
    destroy_towers(game);
    free(game->settings);
    sfClock_destroy(game->game_time);
    sfRenderWindow_destroy(game->window);
    free(game);
}
