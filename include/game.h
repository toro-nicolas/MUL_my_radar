/*
** EPITECH PROJECT, 2023
** myhunter
** File description:
** The game.h
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <ncurses.h>
#include "mycsfml.h"

#ifndef GAME_H_
    #define GAME_H_

typedef enum bool_s {
    OFF,
    ON,
    UNKNOW
} bool_t;

/* Towers structs */
typedef struct tower_s {
    sfVector2f *position;
    float radius;
    struct tower_s *next;
} tower_t;

typedef struct tower_list_s {
    tower_t *tower;
    sfVector2f window_pos;
    struct tower_list_s *next_tower;
} tower_list_t;

/* Planes structs */
typedef struct plane_s {
    sfVector2f *position;
    sfVector2f *end_position;
    float speed;
    float delay;
    sfVector2f *direction;
    sfVector2f windows_pos;
    int is_alive;
    int size;
    struct plane_s *next;
} plane_t;

typedef struct plane_list_s {
    plane_t *plane;
    struct plane_list_s *next_plane;
} plane_list_t;

/* Corners structs */
typedef struct corner_s {
    sfIntRect area;
    tower_list_t *tower_list;
    plane_list_t *plane_list;
    struct corner_s *next_corner;
} corner_t;

/* Game struct */
typedef struct settings_s {
    bool_t hitboxes;
    bool_t sprites;
    bool_t pause;
    bool_t panel;
    int fps_number;
    bool_t fps;
    bool_t time;
    bool_t corners;
    bool_t music;
    int game_speed;
} settings_t;

typedef struct display_s {
    sfTexture *texture;
    sfSprite *background;
    sfSprite *tower;
    sfSprite *plane;
    sfCircleShape *tower_shape;
    sfRectangleShape *plane_shape;
    sfRectangleShape *corner_shape;
    sfFont *game_font;
    sfText *game_text;
    sfMusic *music;
} display_t;

typedef struct game_s {
    sfRenderWindow *window;
    sfEvent event;
    settings_t *settings;
    sfClock *game_time;
    display_t *display;
    tower_t *tower_list;
    plane_t *plane_list;
    corner_t *corner_list;
    sfClock *frames_clock;
    float time_between_frames;
} game_t;

/* Get infos */
int strict_getnbr(char *number);
float strict_getnbr_float(char const *str);
void get_best_direction(plane_t *plane);
sfIntRect get_plane_rect(plane_t *plane, sfVector2f window_pos);
int verify_in_tower(game_t *game, corner_t *corner, plane_t *plane);

/* Init game */
int load_file(game_t *game, char *file_path);
void set_corner(game_t *game);
game_t *create_game(char *file_path);
void destroy_game(game_t *game);

/* Destroy plane */
void destroy_plane(game_t *game,
    plane_t **previous_plane, plane_t **current_plane);
void destroy_plane_in_plane_list(plane_list_t **plane_list,
    plane_list_t **previous_plane, plane_list_t **current_plane);
void check_plane_arrived(game_t *game);
void destroy_all_planes_in_a_corner(corner_t *corner);

/* Draw */
void draw_simulation_panel(game_t *game);
void draw_towers(game_t *game);
void draw_planes(game_t *game);
void draw_corners(game_t *game);
void draw_fps(game_t *game);
void draw_time(game_t *game);
void draw_speed(game_t *game);

/* Update game */
void update_corner(game_t *game);
void check_collision(game_t *game);
void move_plane(game_t *game);
void display_game(game_t *game);

/* Event */
void analyse_events(game_t *game, sfEvent event);

#endif /* GAME_H_ */
