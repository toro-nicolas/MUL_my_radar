/*
** EPITECH PROJECT, 2023
** myradar
** File description:
** The update_game.c
*/

#include "../include/game.h"

void display_game(game_t *game)
{
    draw_simulation_panel(game);
    check_plane_arrived(game);
    update_corner(game);
    sfRenderWindow_clear(game->window, sfBlack);
    while (sfRenderWindow_pollEvent(game->window, &game->event))
        analyse_events(game, game->event);
    sfRenderWindow_drawSprite(game->window, game->display->background, NULL);
    check_collision(game);
    draw_towers(game);
    draw_planes(game);
    move_plane(game);
    draw_corners(game);
    draw_fps(game);
    draw_time(game);
    draw_speed(game);
    sfRenderWindow_display(game->window);
}
