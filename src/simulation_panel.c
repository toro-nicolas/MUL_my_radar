/*
** EPITECH PROJECT, 2023
** myradar
** File description:
** The simulation_panel.c
*/

#include "../include/game.h"

/*static int print_status(game_t *game, plane_t *plane)
{
    if (plane->delay != 0)
        return printw("(will take off in %f seconds)\n",
        (float)plane->delay - (float)(sfClock_getElapsedTime
        (game->game_time).microseconds / 1000000.0));
    if (plane->is_alive == 0)
        return printw("(crashed or landed)\n");
    if (plane->is_alive == 1)
        return printw("(flying)\n");
    if (plane->is_alive == 2)
        return printw("(flying in a tower)\n");
    return printw("\n");
}

static void print_planes(game_t *game, int *lines)
{
    printw("Planes :\n");
    for (plane_t *plane = game->plane_list; *lines < LINES && plane != NULL;
    plane = plane->next) {
        printw("Plane in [%f; %f]\t(speed: %f)\t",
        plane->position->x, plane->position->y,
        (float)plane->speed * game->settings->game_speed);
        print_status(game, plane);
        (*lines)++;
    }
}

static void print_towers(game_t *game, int *lines)
{
    printw("Towers :\n");
    for (tower_t *tower = game->tower_list; *lines < LINES && tower != NULL;
    tower = tower->next) {
        printw("Tower in [%f; %f]\t(radius: %f)\n",
        tower->position->x, tower->position->y, (float) tower->radius);
        (*lines)++;
    }
}

void draw_simulation_panel(game_t *game)
{
    int lines = 3;

    if (game->settings->panel && LINES > 3) {
        erase();
        printw("[ SIMULATION PANEL ]\n");
        print_towers(game, &lines);
        print_planes(game, &lines);
        refresh();
    }
}*/
void draw_simulation_panel(game_t *game)
{
    return;
}
