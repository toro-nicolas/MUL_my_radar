/*
** EPITECH PROJECT, 2023
** myradar
** File description:
** The draw_game.c
*/

#include "../include/game.h"

void draw_corners(game_t *game)
{
    if (game->settings->corners) {
        for (corner_t *corner = game->corner_list; corner != NULL;
        corner = corner->next_corner) {
            sfRectangleShape_setPosition(game->display->corner_shape,
            (sfVector2f){corner->area.left, corner->area.top});
            sfRenderWindow_drawRectangleShape(game->window,
            game->display->corner_shape, NULL);
        }
    }
}

void draw_fps(game_t *game)
{
    int fps = get_fps();
    char *fps_text;
    char *fps_nb;

    if (fps != -1)
        game->settings->fps_number = fps;
    if (game->settings->fps) {
        fps_nb = my_str_nbr(game->settings->fps_number);
        sfText_setPosition(game->display->game_text, (sfVector2f){0, -10});
        fps_text = malloc(sizeof(char) * (8 + my_strlen(fps_nb)));
        my_strcpy(fps_text, "FPS: \0");
        my_strcat(fps_text, fps_nb);
        fps_text[5 + my_strlen(fps_nb)] = '\0';
        sfText_setString(game->display->game_text, fps_text);
        sfRenderWindow_drawText(game->window, game->display->game_text, NULL);
        free(fps_text);
        free(fps_nb);
    }
}

static void check_add_zero(char *time_text, char *time)
{
    if (my_strlen(time) == 1)
        my_strcat(time_text, "0");
}

static char *get_time_text(sfClock *time)
{
    sfInt64 sec = sfClock_getElapsedTime(time).microseconds / 1000000.0;
    char *seconds = my_str_nbr(sec % 60);
    char *minutes = my_str_nbr((sec / 60) % 60);
    char *hours = my_str_nbr((sec / 60) / 60);
    char *time_text = malloc(sizeof(char) * (10 + my_strlen(hours)));

    my_strcpy(time_text, "\0");
    my_strcat(time_text, hours);
    my_strcat(time_text, ":");
    check_add_zero(time_text, minutes);
    my_strcat(time_text, minutes);
    my_strcat(time_text, ":");
    check_add_zero(time_text, seconds);
    my_strcat(time_text, seconds);
    time_text[7 + my_strlen(hours)] = '\0';
    free(seconds);
    free(minutes);
    free(hours);
    return time_text;
}

void draw_time(game_t *game)
{
    char *time_text;

    if (game->settings->time) {
        time_text = get_time_text(game->game_time);
        sfText_setString(game->display->game_text, time_text);
        sfText_setPosition(game->display->game_text, (sfVector2f)
        {1910 - sfText_getGlobalBounds(game->display->game_text).width, -10});
        sfRenderWindow_drawText(game->window, game->display->game_text, NULL);
        free(time_text);
    }
}

void draw_speed(game_t *game)
{
    char *speed = my_str_nbr(game->settings->game_speed);
    char *speed_text = malloc(sizeof(char) * (4 + my_strlen(speed)));

    speed_text[0] = 'x';
    speed_text[1] = '\0';
    my_strcat(speed_text, speed);
    sfText_setString(game->display->game_text, speed_text);
    sfText_setPosition(game->display->game_text, (sfVector2f)
    {1910 - sfText_getGlobalBounds(game->display->game_text).width, 30});
    sfRenderWindow_drawText(game->window, game->display->game_text, NULL);
    free(speed_text);
    free(speed);
}
