# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/16 23:59:21 by thi-huon          #+#    #+#              #
#    Updated: 2025/10/17 00:57:58 by thi-huon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 				= cub3D
NAME_BONUS			= cub3D_bonus

CC              := cc
CFLAGS          := -Wall -Wextra -Werror
INCLUDE         := -I ./library -I ./includes -I ./MLX42/include

LIBFT_DIR       := ./library
LIBFT           := $(LIBFT_DIR)/libft.a

MLX42_DIR       := ./MLX42
MLX42           := $(MLX42_DIR)/build/libmlx42.a
LINUX_GL_FLAGS  := -lglfw -lm -lX11 -lXext -lXrandr -lXinerama -lXcursor -lXi

# Source layout
MAN_DIR         := ./srcs/mandatory
BN_DIR          := ./srcs/bonus

# Mandatory file lists
MAIN_C                  := main.c

INPUT_VALIDATIONS_C     := ft_clean_arr.c get_color.c readline.c utils.c error_handling.c

MAP_C                   := grid_validation.c is_closed.c map_utils.c path_check.c png_validation.c \
						read_elements.c read_grid.c read_map.c

RENDER_ASSETS_C         := render_assets.c image_utils.c load_textures.c

INIT_AND_DISPLAY_C      := display.c init.c

INPUT_C                 := input_camera.c input_movement.c input_utils.c

RAY_CASTING_C           := wall_column.c dda_core.c dda_hit.c ray_casting.c

CLEAN_UP_C              := clean_game.c error_clean.c

# Compose mandatory sources
MAN_SRCS := \
  $(addprefix $(MAN_DIR)/main/,               $(MAIN_C)) \
  $(addprefix $(MAN_DIR)/parsing/input_validations/, $(INPUT_VALIDATIONS_C)) \
  $(addprefix $(MAN_DIR)/parsing/map/,       $(MAP_C)) \
  $(addprefix $(MAN_DIR)/execution/render_assets/,    $(RENDER_ASSETS_C)) \
  $(addprefix $(MAN_DIR)/execution/init_and_display/, $(INIT_AND_DISPLAY_C)) \
  $(addprefix $(MAN_DIR)/execution/input/,           $(INPUT_C)) \
  $(addprefix $(MAN_DIR)/execution/mini_map/,        $(MINI_MAP_C)) \
  $(addprefix $(MAN_DIR)/execution/ray_casting/,     $(RAY_CASTING_C)) \
  $(addprefix $(MAN_DIR)/execution/clean_up/,        $(CLEAN_UP_C))


# Bonus file lists
BN_MAIN_C                  := main_bonus.c

BN_INPUT_VALIDATIONS_C     := ft_clean_arr_bonus.c get_color_bonus.c readline_bonus.c utils_bonus.c \
							error_handling_bonus.c

BN_MAP_C                   := grid_validation_bonus.c is_closed_bonus.c map_utils_bonus.c path_check_bonus.c \
                            png_validation_bonus.c read_elements_bonus.c read_grid_bonus.c read_map_bonus.c

BN_RENDER_ASSETS_C         := render_assets_bonus.c image_utils_bonus.c load_textures_bonus.c

BN_INIT_AND_DISPLAY_C      := display_bonus.c init_bonus.c

BN_INPUT_C                 := input_camera_bonus.c input_movement_bonus.c input_utils_bonus.c

BN_MINI_MAP_C              := minimap_bonus.c minimap_player_bonus.c minimap_viewport_bonus.c

BN_RAY_CASTING_C           := wall_column_bonus.c dda_core_bonus.c dda_hit_bonus.c ray_casting_bonus.c

BN_CLEAN_UP_C              := clean_game_bonus.c error_clean_bonus.c

BN_SRCS := \
  $(addprefix $(BN_DIR)/main/,               $(BN_MAIN_C)) \
  $(addprefix $(BN_DIR)/parsing/input_validations/, $(BN_INPUT_VALIDATIONS_C)) \
  $(addprefix $(BN_DIR)/parsing/map/,       $(BN_MAP_C)) \
  $(addprefix $(BN_DIR)/execution/render_assets/,    $(BN_RENDER_ASSETS_C)) \
  $(addprefix $(BN_DIR)/execution/init_and_display/, $(BN_INIT_AND_DISPLAY_C)) \
  $(addprefix $(BN_DIR)/execution/input/,           $(BN_INPUT_C)) \
  $(addprefix $(BN_DIR)/execution/mini_map/,        $(BN_MINI_MAP_C)) \
  $(addprefix $(BN_DIR)/execution/ray_casting/,     $(BN_RAY_CASTING_C)) \
  $(addprefix $(BN_DIR)/execution/clean_up/,        $(BN_CLEAN_UP_C))

# Objects
MAN_OBJS := $(MAN_SRCS:.c=.o)
BN_OBJS  := $(BN_SRCS:.c=.o)

# Default target
all: mandatory

# Build rules
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# # Build executable
# ${NAME}: ${OBJS} ${LIBFT} .mlx42
# 	${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${MLX42} ${MLX42_DIR}/build/_deps/glfw-build/src/libglfw3.a -lm -lX11 -lXext -lXrandr -lXinerama -lXcursor -lXi -o ${NAME}

# Mandatory
mandatory: .mandatory
.mandatory: $(LIBFT) .mlx42 $(MAN_OBJS)
	$(CC) $(CFLAGS) $(MAN_OBJS) $(LIBFT) $(MLX42) $(LINUX_GL_FLAGS) -o $(NAME)
	@touch .mandatory
	@rm -f .bonus

# Bonus
bonus: .bonus
.bonus: $(LIBFT) .mlx42 $(BN_OBJS)
	$(CC) $(CFLAGS) $(BN_OBJS) $(LIBFT) $(MLX42) $(LINUX_GL_FLAGS) -o $(NAME_BONUS)
	@touch .bonus
	@rm -f .mandatory

# Build libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Build MLX42
.mlx42:
	@printf "\033[1;33mMLX42\033[1;32m 💻Setting up…\n"
	@rm -rf $(MLX42_DIR)
	@{ \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR) > /dev/null 2>&1 && \
		cd $(MLX42_DIR) && mkdir -p build && cd build && \
		cmake .. > /dev/null 2>&1 && \
		cmake --build . -j4 > /dev/null 2>&1; \
	} || { echo "\033[0;31m❌ MLX42 build failed\033[0m"; exit 1; }
	@rm -rf $(MLX42_DIR)/.git
	@touch .mlx42
	@echo "\033[1;33mMLX42\033[1;32m ✅Done"

$(MLX42): .mlx42

# Clean object files
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(MAN_OBJS) $(BN_OBJS)

# Clean everything
fclean: clean
	rm -f $(NAME)  $(NAME_BONUS) .mlx42 .mandatory .bonus
	rm -rf $(MLX42_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild
re: fclean all

# Phony targets
.PHONY: all mandatory bonus clean fclean re
