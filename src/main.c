/*
** EPITECH PROJECT, 2023
** myradar
** File description:
** The main.c
*/

#include "../include/game.h"

int init_game(char *file_path)
{
    game_t *game = create_game(file_path);

    if (game == NULL || !game->window)
        return EXIT_FAILURE;
    while (sfRenderWindow_isOpen(game->window)) {
        game->time_between_frames =
            sfClock_restart(game->frames_clock).microseconds / 1000000.0;
        display_game(game);
        if (game->plane_list == NULL)
            break;
    }
    if (game->plane_list == NULL)
        my_putstr("All planes have landed !\n");
    destroy_game(game);
    return EXIT_SUCCESS;
}

int show_help(void)
{
    my_putstr("Air traffic simulation panel\n\nUSAGE\n"
        "    ./my_radar map_path\n"
        "    map_path          The map that will be loaded.\n\n"
        "OPTIONS:\n"
        "    -h                print the usage and quit.\n\n"
        "USER INTERACTIONS\n"
        "    'L' key           enable/disable hitboxes and areas.\n"
        "    'S' key           enable/disable sprites.\n"
        "    'Space' key       pause the simulation.\n"
        "    'Tab' key         enable/disable simulation panel. (only in "
        "bonus)\n"
        "    'T' key           enable/disable time counter.\n"
        "    'F' key           enable/disable FPS counter.\n"
        "    'C' key           enable/disable corners.\n"
        "    'P' key           enable/disable music.\n"
        "    'Right' key       increase game speed.\n"
        "    'Left' key        decrease game speed.\n"
        "    'Up' key          set FPS limit to 120.\n"
        "    'Down' key        set FPS limit to 30.\n");
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        my_putstr_error("my_radar: invalid option\n"
            "Try './my_radar --help' for more information.\n");
        return 84;
    } else {
        if (my_strcmp(argv[1], "-h") == 0 || my_strcmp(argv[1], "--help") == 0)
            return show_help();
        srand(time(NULL));
        return init_game(argv[1]);
    }
}
