# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sperron <sperron@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 12:43:23 by sperron           #+#    #+#              #
#    Updated: 2024/11/18 07:32:08 by sperron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME = libgarbage_descriptor.a
CC = cc -g3
CFLAGS = -Wall -Wextra -Werror

SRC = src/gd_add.c \
	src/gd_init.c \
	src/gd_clear.c \
	src/gd_utils.c

OBJECTS = $(SRC:.c=.o)

#################################################################################

# Couleurs pour l'affichage
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
CYAN = \033[0;36m
NC = \033[0m

#################################################################################

OBJ = $(SRC:.c=.o)

# Règle par défaut
all: $(NAME)

# Compilation des fichiers objets
%.o: %.c
	@echo "$(YELLOW)🔨 Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)✅ $< compiled!$(NC)"

# Création de l'exécutable
$(NAME): $(OBJ)
	@echo "$(BLUE)🔗 Creating static library...$(NC)"
	@ar rcs $(NAME) $(OBJ)
	@echo "$(GREEN)✅ $@ created!$(NC)"

clean:
	@echo "$(YELLOW)🗑️ Cleaning up object files...$(NC)"
	@rm -f $(OBJECTS)
	@echo "$(YELLOW)🗑️ $(OBJECTS) deleted!$(NC)"



fclean: clean
	@echo "$(RED)🗑️ Removing executable...$(NC)"
	@rm -rf $(NAME)
	@echo "$(GREEN)🗑️ $(NAME) deleted!$(NC)"

# Recompile tout
re: fclean all

.PHONY: re all clean fclean