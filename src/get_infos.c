/*
** EPITECH PROJECT, 2024
** myradar
** File description:
** The get_infos.c
*/

#include "../include/game.h"

int strict_getnbr(char *number)
{
    int nb = 0;

    if (number[0] == '\0')
        return -1;
    for (int index = 0; number[index] != '\0'; index++) {
        if (number[index] < '0' || number[index] > '9')
            return -1;
        else
            nb = nb * 10 + (number[index] - 48);
    }
    return nb;
}

float strict_getnbr_float(char const *str)
{
    float convert = 0;
    int index = 0;
    float index_float = 0.1;

    if (str[0] < '0' || str[0] > '9')
        return -1;
    for (; str[index] >= '0' && str[index] <= '9'; index++)
        convert = convert * 10 + (str[index] - 48);
    if (str[index] == '.') {
        index++;
        for (; str[index] >= '0' && str[index] <= '9'; index++) {
            convert = convert + index_float * (str[index] - 48);
            index_float = index_float * 0.1;
        }
    }
    return convert;
}

static double get_distance(sfVector2f *position, sfVector2f *end_position)
{
    return sqrt(pow(end_position->x - position->x, 2) +
        pow(end_position->y - position->y, 2));
}

static sfVector2f *get_direction(sfVector2f *position,
    sfVector2f *end_position)
{
    sfVector2f *direction = malloc(sizeof(sfVector2f));
    float direction_x = end_position->x - position->x;
    float direction_y = end_position->y - position->y;
    float steps = (ABS(direction_x) > ABS(direction_y)) ?
        ABS(direction_x) : ABS(direction_y);

    direction->x = (direction_x / steps);
    direction->y = (direction_y / steps);
    return direction;
}

void get_best_direction(plane_t *plane)
{
    int best_index = 0;
    sfVector2f windows_pos[5] = {(sfVector2f){0, 0}, (sfVector2f){-1920, 0},
    (sfVector2f){0, 1080}, (sfVector2f){1920, 0}, (sfVector2f){0, -1080}};
    double distances[5];

    for (int index = 0; index < 5; index++)
        distances[index] = get_distance(plane->position, &(sfVector2f)
        {plane->end_position->x + windows_pos[index].x,
        plane->end_position->y + windows_pos[index].y});
    for (int index = 0; index < 5; index++) {
        if (distances[index] < distances[best_index])
            best_index = index;
    }
    plane->windows_pos = windows_pos[best_index];
    plane->direction = get_direction(plane->position, &(sfVector2f)
    {plane->end_position->x + plane->windows_pos.x, plane->end_position->y +
    plane->windows_pos.y});
}

sfIntRect get_plane_rect(plane_t *plane, sfVector2f window_pos)
{
    return (sfIntRect){plane->position->x - (plane->size / 2.0) + window_pos.x,
    plane->position->y - (plane->size / 2.0) + window_pos.y, plane->size + 2,
    plane->size + 2};
}
