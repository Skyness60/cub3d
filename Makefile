NAME = cub3d

CC = cc -g3

CFLAGS = -Wall -Wextra -Werror -MMD -MP

LINKLIBS =	-L./export/libft -lft \
			-L./export/garbage_descriptor -lgarbage_descriptor \
			-L./export/printf -lftprintf \
			-L./export/gnl -lftgnl \
			-L./export/garbage_collector -lgarbage_collector

SRC = 		src/cub3d.c \

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
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LINKLIBS)
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
	@echo $(RED)🗑️ $(NAME) and $(BONUS) deleted! $(NC)

re: fclean all

.PHONY: re all clean fclean