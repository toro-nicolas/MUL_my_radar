/*
** EPITECH PROJECT, 2023
** myradar
** File description:
** The load_file.c
*/

#include "../include/game.h"

static void add_tower_in_corner(corner_t *corner, tower_t *tower,
    sfVector2f window_pos)
{
    tower_list_t *new_list = malloc(sizeof(tower_list_t));

    new_list->tower = tower;
    new_list->window_pos = window_pos;
    if (corner->tower_list == NULL)
        new_list->next_tower = NULL;
    else
        new_list->next_tower = corner->tower_list;
    corner->tower_list = new_list;
}

static void add_tower_in_different_position(corner_t *corner, tower_t *tower,
    sfVector2f *position, float radius)
{
    sfVector2f windows_pos[5] = {(sfVector2f){0, 0}, (sfVector2f){-1920, 0},
        (sfVector2f){0, 1080}, (sfVector2f){1920, 0}, (sfVector2f){0, -1080}};

    for (int index = 0; index < 5; index++) {
        if (rect_is_intersecting_circle(corner->area, (sfVector2f)
        {position->x + windows_pos[index].x,
        position->y + windows_pos[index].y}, radius))
            add_tower_in_corner(corner, tower, windows_pos[index]);
    }
}

static tower_t *add_tower_in_list(game_t *game,
    sfVector2f *position, float radius)
{
    tower_t *new_list = malloc(sizeof(tower_t));

    new_list->position = position;
    new_list->radius = radius;
    if (game->tower_list == NULL)
        new_list->next = NULL;
    else
        new_list->next = game->tower_list;
    game->tower_list = new_list;
    return new_list;
}

static int add_tower(game_t *game, char **file_elements, int *index)
{
    float x = strict_getnbr_float(file_elements[*index + 1]);
    float y = strict_getnbr_float(file_elements[*index + 2]);
    float radius = strict_getnbr_float(file_elements[*index + 3]);
    sfVector2f *position = malloc(sizeof(sfVector2f));
    tower_t *tower;

    if (x == -1 || y == -1 || x > 1920 || y > 1080 ||
    radius == -1 || radius > 100)
        return 1;
    radius = 1920 * (radius / 100.0);
    position->x = x;
    position->y = y;
    tower = add_tower_in_list(game, position, radius);
    for (corner_t *corner = game->corner_list; corner != NULL;
    corner = corner->next_corner)
        add_tower_in_different_position(corner, tower, position, radius);
    *index = *index + 3;
    return 0;
}

static void add_plane_in_list(game_t *game,
    sfVector2f *position, sfVector2f *end_position, float *values)
{
    plane_t *new_list = malloc(sizeof(plane_t));

    new_list->position = position;
    new_list->end_position = end_position;
    new_list->speed = values[0];
    new_list->delay = values[1];
    get_best_direction(new_list);
    new_list->is_alive = 1;
    new_list->size = rand() % 41 + 15;
    if (game->plane_list == NULL)
        new_list->next = NULL;
    else
        new_list->next = game->plane_list;
    game->plane_list = new_list;
}

static int add_plane(game_t *game, char **file_elements, int *index)
{
    float x = strict_getnbr_float(file_elements[*index + 1]);
    float y = strict_getnbr_float(file_elements[*index + 2]);
    float x_end = strict_getnbr_float(file_elements[*index + 3]);
    float y_end = strict_getnbr_float(file_elements[*index + 4]);
    float speed = strict_getnbr_float(file_elements[*index + 5]);
    float time = strict_getnbr_float(file_elements[*index + 6]);
    sfVector2f *position = malloc(sizeof(sfVector2f));
    sfVector2f *end_position = malloc(sizeof(sfVector2f));
    float values[2] = {speed, time};

    if (x == -1 || y == -1 || x > 1920 || y > 1080 || x_end == -1 ||
    y_end == -1 || x_end > 1920 || y_end > 1080 || speed <= 0 || time == -1)
        return 1;
    position->x = x;
    position->y = y;
    end_position->x = x_end;
    end_position->y = y_end;
    add_plane_in_list(game, position, end_position, values);
    *index = *index + 6;
    return 0;
}

static void free_content(char *file_content, char **file_elements)
{
    free(file_content);
    for (int index = 0; file_elements[index] != NULL; index++)
        free(file_elements[index]);
    free(file_elements);
}

static int get_file_content(game_t *game, char *file_content)
{
    char **file_elements = my_str_to_word_array_select(file_content, " \n");

    for (int index = 0; file_elements[index] != NULL; index++) {
        if ((my_strcmp(file_elements[index], "T") != 0 &&
        my_strcmp(file_elements[index], "A") != 0) ||
        (my_strcmp(file_elements[index], "T") == 0 &&
        add_tower(game, file_elements, &index)) ||
        (my_strcmp(file_elements[index], "A") == 0 &&
        add_plane(game, file_elements, &index))) {
            free_content(file_content, file_elements);
            return 1;
        }
    }
    free_content(file_content, file_elements);
    return 0;
}

int load_file(game_t *game, char *file_path)
{
    int file = open(file_path, O_RDONLY);
    struct stat file_infos;
    char *file_content;

    if (file < 0 || stat(file_path, &file_infos) < 0)
        return 1;
    file_content = malloc(sizeof(char) * (file_infos.st_size + 1));
    if (read(file, file_content, file_infos.st_size) < 0)
        return 1;
    file_content[file_infos.st_size] = '\0';
    return get_file_content(game, file_content);
}
