/*
** EPITECH PROJECT, 2023
** myradar
** File description:
** The corner.c
*/

#include "../include/game.h"

static void top_left(game_t *game)
{
    corner_t *corner1 = malloc(sizeof(corner_t));
    corner_t *corner2 = malloc(sizeof(corner_t));

    corner1->area = (sfIntRect){0, 0, 480, 270};
    corner1->tower_list = NULL;
    corner1->plane_list = NULL;
    corner1->next_corner = NULL;
    game->corner_list = corner1;
    corner2->area = (sfIntRect){480, 0, 480, 270};
    corner2->tower_list = NULL;
    corner2->plane_list = NULL;
    corner2->next_corner = game->corner_list;
    game->corner_list = corner2;
}

static void top_right(game_t *game)
{
    corner_t *corner1 = malloc(sizeof(corner_t));
    corner_t *corner2 = malloc(sizeof(corner_t));

    corner1->area = (sfIntRect){480 * 2, 0, 480, 270};
    corner1->tower_list = NULL;
    corner1->plane_list = NULL;
    corner1->next_corner = game->corner_list;
    game->corner_list = corner1;
    corner2->area = (sfIntRect){480 * 3, 0, 480, 270};
    corner2->tower_list = NULL;
    corner2->plane_list = NULL;
    corner2->next_corner = game->corner_list;
    game->corner_list = corner2;
}

static void top_left_middle(game_t *game)
{
    corner_t *corner1 = malloc(sizeof(corner_t));
    corner_t *corner2 = malloc(sizeof(corner_t));

    corner1->area = (sfIntRect){0, 270, 480, 270};
    corner1->tower_list = NULL;
    corner1->plane_list = NULL;
    corner1->next_corner = game->corner_list;
    game->corner_list = corner1;
    corner2->area = (sfIntRect){480, 270, 480, 270};
    corner2->tower_list = NULL;
    corner2->plane_list = NULL;
    corner2->next_corner = game->corner_list;
    game->corner_list = corner2;
}

static void top_right_middle(game_t *game)
{
    corner_t *corner1 = malloc(sizeof(corner_t));
    corner_t *corner2 = malloc(sizeof(corner_t));

    corner1->area = (sfIntRect){480 * 2, 270, 480, 270};
    corner1->tower_list = NULL;
    corner1->plane_list = NULL;
    corner1->next_corner = game->corner_list;
    game->corner_list = corner1;
    corner2->area = (sfIntRect){480 * 3, 270, 480, 270};
    corner2->tower_list = NULL;
    corner2->plane_list = NULL;
    corner2->next_corner = game->corner_list;
    game->corner_list = corner2;
}

static void bottom_left_middle(game_t *game)
{
    corner_t *corner1 = malloc(sizeof(corner_t));
    corner_t *corner2 = malloc(sizeof(corner_t));

    corner1->area = (sfIntRect){0, 270 * 2, 480, 270};
    corner1->tower_list = NULL;
    corner1->plane_list = NULL;
    corner1->next_corner = game->corner_list;
    game->corner_list = corner1;
    corner2->area = (sfIntRect){480, 270 * 2, 480, 270};
    corner2->tower_list = NULL;
    corner2->plane_list = NULL;
    corner2->next_corner = game->corner_list;
    game->corner_list = corner2;
}

static void bottom_right_middle(game_t *game)
{
    corner_t *corner1 = malloc(sizeof(corner_t));
    corner_t *corner2 = malloc(sizeof(corner_t));

    corner1->area = (sfIntRect){480 * 2, 270 * 2, 480, 270};
    corner1->tower_list = NULL;
    corner1->plane_list = NULL;
    corner1->next_corner = game->corner_list;
    game->corner_list = corner1;
    corner2->area = (sfIntRect){480 * 3, 270 * 2, 480, 270};
    corner2->tower_list = NULL;
    corner2->plane_list = NULL;
    corner2->next_corner = game->corner_list;
    game->corner_list = corner2;
}

static void bottom_left(game_t *game)
{
    corner_t *corner1 = malloc(sizeof(corner_t));
    corner_t *corner2 = malloc(sizeof(corner_t));

    corner1->area = (sfIntRect){0, 270 * 3, 480, 270};
    corner1->tower_list = NULL;
    corner1->plane_list = NULL;
    corner1->next_corner = game->corner_list;
    game->corner_list = corner1;
    corner2->area = (sfIntRect){480, 270 * 3, 480, 270};
    corner2->tower_list = NULL;
    corner2->plane_list = NULL;
    corner2->next_corner = game->corner_list;
    game->corner_list = corner2;
}

static void bottom_right(game_t *game)
{
    corner_t *corner1 = malloc(sizeof(corner_t));
    corner_t *corner2 = malloc(sizeof(corner_t));

    corner1->area = (sfIntRect){480 * 2, 270 * 3, 480, 270};
    corner1->tower_list = NULL;
    corner1->plane_list = NULL;
    corner1->next_corner = game->corner_list;
    game->corner_list = corner1;
    corner2->area = (sfIntRect){480 * 3, 270 * 3, 480, 270};
    corner2->tower_list = NULL;
    corner2->plane_list = NULL;
    corner2->next_corner = game->corner_list;
    game->corner_list = corner2;
}

void set_corner(game_t *game)
{
    top_left(game);
    top_right(game);
    top_left_middle(game);
    top_right_middle(game);
    bottom_left_middle(game);
    bottom_right_middle(game);
    bottom_left(game);
    bottom_right(game);
}
