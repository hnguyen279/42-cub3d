NAME := cub3d

CC := cc
CFLAGS := -Wall -Wextra -Werror

LIBFT_DIR		:= ./library/libft
LIBFT			:= ${LIBFT_DIR}/libft.a

MLX42_DIR		:= ./MLX42
MLX42			:= ${MLX42_DIR}/build/libmlx42.a

INCLUDE 		:= -I ${LIBFT_DIR} -I ./includes/ -I ${MLX42_DIR}/include

# Source directories
MAIN			:= ./srcs/main
PARSING			:= ./srcs/parsing
EXECUTION		:= ./srcs/execution

# Source files
MAIN_C			:= main.c

INPUT_VALIDATIONS_C := ft_clean_arr.c \
					   get_color.c \
					   readline.c \
					   utils.c \
					   error_handling.c

MAP_C			:= grid_validation.c \
				   is_closed.c \
				   map_utils.c \
				   png_validation.c \
				   read_elements.c \
				   read_grid.c \
				   read_map.c

EXECUTION_C		:= textures.c \
				   render.c

# All source files
SRCS			:= $(addprefix ${MAIN}/, ${MAIN_C}) \
				   $(addprefix ${PARSING}/input_validations/, ${INPUT_VALIDATIONS_C}) \
				   $(addprefix ${PARSING}/map/, ${MAP_C}) \
				   $(addprefix ${EXECUTION}/, ${EXECUTION_C})

# Object files
OBJS			:= ${SRCS:.c=.o}

# Default target
all: ${LIBFT} .mlx42 ${NAME}

# Compile object files
%.o: %.c
	${CC} ${CFLAGS} -o $@ -c $< ${INCLUDE}

# Build executable
${NAME}: ${OBJS} ${LIBFT} .mlx42
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${MLX42} ${MLX42_DIR}/build/_deps/glfw-build/src/libglfw3.a -lm -lX11 -lXext -lXrandr -lXinerama -lXcursor -lXi -o ${NAME}

# Build libft
${LIBFT}:
	@$(MAKE) -C ${LIBFT_DIR}

# Build MLX42
.mlx42:
	@printf "\033[1;33mMLX42\033[1;32m 💻Setting up…\n"
	@rm -rf $(MLX42_DIR)
	@{ \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR) > /dev/null 2>&1 && \
		cd $(MLX42_DIR) && \
		mkdir -p build && cd build && \
		cmake .. > /dev/null 2>&1 && \
		cmake --build . -j4 > /dev/null 2>&1; \
	} || { echo "\033[0;31m❌ MLX42 build failed\033[0m"; exit 1; }
	@rm -rf $(MLX42_DIR)/.git
	@touch .mlx42
	@echo "\033[1;33mMLX42\033[1;32m ✅Done"

# Clean object files
clean:
	rm -f ${OBJS}
	@$(MAKE) -C ${LIBFT_DIR} clean

# Clean everything
fclean: clean
	rm -f ${NAME}
	rm -f .mlx42
	@$(MAKE) -C ${LIBFT_DIR} fclean

# Rebuild
re: fclean all

# Phony targets
.PHONY: all clean fclean re
