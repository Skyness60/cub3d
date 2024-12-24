NAME = cub3d

CC = cc -g3

INCLUDE_DIR = ./include/

CFLAGS = -g -Wall -Wextra -Werror -I$(INCLUDE_DIR)


LINKLIBS =	-L./export/libft -lft \
			-L./export/garbage_descriptor -lgarbage_descriptor \
			-L./export/printf -lftprintf \
			-L./export/gnl -lftgnl \
			-L./export/garbage_collector -lgarbage_collector

SRC = 		src/cub3d.c \
			src/parsing/init/init.c \
			src/parsing/utils/ft_free.c \
			src/parsing/cub/cub.c \
			src/parsing/cub/cub_file.c \
			src/parsing/cub/cub_map.c \
			src/parsing/cub/cub_texture.c \
			src/parsing/cub/cub_texture_color.c \
			src/parsing/check/check_name.c \
			src/parsing/utils/close_all.c \
			src/parsing/check/check_map.c \
			src/parsing/utils/utils_parsing.c \
			src/parsing/cub/cub_map_utils.c \
			src/parsing/algo/flood_fill.c \
			src/game/open/open_cub3d.c \
			src/game/handle/handle_close.c \
			src/game/handle/handle_move.c \
			src/game/handle/handle_move_utils.c \
			src/game/game_cub3d.c \
			src/render/raycasting.c \
			src/render/display.c \
			src/parsing/utils/convert_color.c \

MLX_PATH = ./mlx/

MINI_LIBX = MiniLibX

MLX_FLAGS = -lmlx -lmlx_Linux -lX11 -lXext -lm

OBJECTS = $(SRC:.c=.o)

#################################################################################

RED = '\033[0;31m'
GREEN = '\033[0;32m'
YELLOW = '\033[0;33m'
BLUE = '\033[0;34m'
PURPLE = '\033[0;35m'
CYAN = '\033[0;36m'
MAGENTA = '\033[0;35m'
NC = '\033[0m'

#################################################################################


OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo $(GREEN)✅ $< compiled! $(NC)

$(NAME) : $(OBJ)
	@make -C ./export/libft --no-print-directory
	@make -C ./export/garbage_collector --no-print-directory
	@make -C ./export/garbage_descriptor --no-print-directory
	@make -C ./export/printf --no-print-directory
	@make -C ./export/gnl --no-print-directory
	@make -C $(MLX_PATH) --no-print-directory
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LINKLIBS) -L$(MLX_PATH) $(MLX_FLAGS)
	@echo $(BLUE)✅ $@ built! $(NC)

clean:
	@rm -f $(OBJECTS)
	@echo $(YELLOW)🗑️ $(OBJECTS) deleted! $(NC)

fclean:	clean
	@rm -rf $(NAME)
	@make fclean -C ./export/libft --no-print-directory
	@make fclean -C ./export/garbage_collector --no-print-directory
	@make fclean -C ./export/garbage_descriptor --no-print-directory
	@make fclean -C ./export/printf --no-print-directory
	@make fclean -C ./export/gnl --no-print-directory
	@make clean -C ${MLX_PATH} --no-print-directory
	@echo $(RED)🗑️ $(NAME) deleted! $(NC)

re: fclean all

.PHONY: re all clean fclean