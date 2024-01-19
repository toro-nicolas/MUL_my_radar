/*
** EPITECH PROJECT, 2023
** myradar
** File description:
** The game.c
*/

#include "../include/game.h"

static void set_settings(game_t *game)
{
    game->settings = malloc(sizeof(settings_t));
    game->settings->hitboxes = ON;
    game->settings->sprites = ON;
    game->settings->pause = OFF;
    game->settings->panel = OFF;
    game->settings->fps_number = 120;
    game->settings->fps = OFF;
    game->settings->time = ON;
    game->settings->corners = OFF;
    game->settings->music = ON;
    game->settings->game_speed = 1;
}

static void set_text_and_music(game_t *game)
{
    game->display->game_font = sfFont_createFromFile("assets/font/font.ttf");
    game->display->game_text = sfText_create();
    sfText_setFont(game->display->game_text, game->display->game_font);
    sfText_setCharacterSize(game->display->game_text, 50);
    sfText_setFillColor(game->display->game_text, sfBlack);
    game->display->music = sfMusic_createFromFile
    ("assets/music/background.ogg");
    sfMusic_setLoop(game->display->music, sfTrue);
    sfMusic_play(game->display->music);
}

static void set_shape(game_t *game)
{
    circle_shape_t tower_shape = {.fill_color = &sfTransparent,
        .outline_color = &sfCyan, .outline_thickness = 2};
    rectangle_shape_t plane_shape = {.fill_color = &sfTransparent,
        .outline_thickness = 2, .outline_color = &sfRed};
    rectangle_shape_t corner_shape = {.fill_color = &sfTransparent,
        .size = &(sfVector2f){480, 270}, .outline_thickness = -2,
        .outline_color = &sfGreen};

    game->display->tower_shape = create_circle_shape(&tower_shape,
        (sfVector2f){0, 0});
    game->display->plane_shape = create_rectangle_shape(&plane_shape,
        (sfVector2f){0, 0});
    game->display->corner_shape = create_rectangle_shape(&corner_shape,
        (sfVector2f){0, 0});
}

static void set_sprite(game_t *game)
{
    sprite_t background = {.rect = &(sfIntRect){0, 0, 1920, 1080}};
    sprite_t tower = {.rect = &(sfIntRect){1920, 0, 512, 512}, .scale =
        &(sfVector2f){0.08, 0.08}, .origin = &(sfVector2f){256, 256}};
    sprite_t plane = {.rect = &(sfIntRect){1920, 512, 285, 268},
        .origin = &(sfVector2f){142.5, 134}};

    game->display = malloc(sizeof(display_t));
    game->display->texture =
        sfTexture_createFromFile("assets/images/texture.png", NULL);
    game->display->background = create_sf_sprite(&background,
        game->display->texture, (sfVector2f){0, 0});
    game->display->tower = create_sf_sprite(&tower,
        game->display->texture, (sfVector2f){0, 0});
    game->display->plane = create_sf_sprite(&plane, game->display->texture,
        (sfVector2f){100, 100});
}

game_t *create_game(char *file_path)
{
    game_t *game = malloc(sizeof(game_t));

    set_corner(game);
    game->tower_list = NULL;
    game->plane_list = NULL;
    if (load_file(game, file_path)) {
        my_putstr_error("Can't read file informations or file not valid.\n");
        return NULL;
    }
    game->window = sfRenderWindow_create((sfVideoMode){
        1920, 1080, 32}, "my_radar", sfClose, NULL);
    game->game_time = sfClock_create();
    set_sprite(game);
    set_shape(game);
    set_text_and_music(game);
    set_settings(game);
    sfRenderWindow_setFramerateLimit(game->window, 120);
    game->frames_clock = sfClock_create();
    game->time_between_frames = 0.0;
    return game;
}
