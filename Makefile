##
## EPITECH PROJECT, 2023
## myradar
## File description:
## The main Makefile of our project
##

NAME		=	my_radar

BUILDDIR 	=	./build
SRCDIR		=	./src

SRCS		+=	main.c
SRCS		+=	verify_in_tower.c
SRCS		+=	get_infos.c
SRCS		+=	draw_game.c
SRCS		+=	draw_entities.c
SRCS		+=	corner.c
SRCS		+=	destroy_game.c
SRCS		+=	event.c
SRCS		+=	game.c
SRCS		+=	update_corner.c
SRCS		+=	update_game.c
SRCS		+=	collision.c
SRCS		+=	destroy_plane.c
SRCS		+=	load_file.c
SRCS		+=	move.c
SRCS		+=	simulation_panel.c

OBJS     	=	$(addprefix $(BUILDDIR)/, $(notdir $(SRCS:.c=.o)))

CFLAGS		=	-Werror -Wextra -g3 -I./include/
CFLAGS		+=	-lcsfml-graphics -lcsfml-system -lcsfml-window -lcsfml-audio

LDFLAGS 	=	-L./lib/ -lmylist -lmycsfml -lmy -lm -lncurses

all: create-build libs $(BUILDDIR) $(NAME)
	@echo -e "\033[1;33mmy_radar compiled.\033[0m"

libs:
	@make --no-print-directory -C./lib/my/
	@make --no-print-directory -C./lib/mylist/
	@make --no-print-directory -C./lib/mycsfml/
	@echo -e "\033[1;33mLibs made.\033[0m"

create-build:
	@mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(NAME)
	@rm -rf ./lib/my/*.a
	@rm -rf ./lib/mylist/*.a
	@rm -rf ./lib/mycsfml/*.a

clean:
	@rm -rf $(BUILDDIR)
	@echo -e "\033[1;31mAll .o deleted.\033[0m"

fclean: clean
	@rm -rf ./lib/*.a
	@rm -rf unit_tests*
	@rm -rf tests/unit_tests*
	@rm -rf vgcore*
	@rm -rf *.log
	@rm -rf $(NAME)
	@echo -e "\033[1;31mProject cleaned.\033[0m"

re:	fclean all

run: re
	@echo -e "\033[1;32mRunning project...\033[0m"
	@./$(NAME)

valgrind: re
	@valgrind -s ./$(NAME)

# Unit tests Makefile
unit_tests:
	@make unit_tests --no-print-directory -C./tests/

tests_run:
	@make tests_run --no-print-directory -C./tests/
	@gcovr
