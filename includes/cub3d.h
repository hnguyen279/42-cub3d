/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-mngu <thi-mngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:57:55 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/09/02 13:33:54 by thi-mngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include "libft.h"
# include "MLX42/MLX42.h"

/* Constants */
# define G_BUFFER 1024
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_ERROR -1

/* Window settings */
# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 800
# define FOV 60.0
# define RAY_STEP 0.1

#define PI 3.14159265359
#define CELL_PX 64
#define M_PLAYER_SIZE 32

/* Element types */
typedef enum e_ele_type
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
}	t_ele_type;

/* Map characters */
# define PLAYER_N 'N'
# define PLAYER_S 'S'
# define PLAYER_E 'E'
# define PLAYER_W 'W'

# define PLAYER "./textures/player.png"
# define SPACE "./textures/space.png"
# define WALL "./textures/wall.png"

/* Data structures */
typedef struct s_dpoint
{
	double	x;
	double	y;
}	t_dpoint;

typedef struct s_player
{
	t_dpoint	cur_pos;
	t_dpoint	prev_pos;
	double		angle;
	int			attack;
}	t_player;

typedef struct s_texture
{
	mlx_texture_t	*tex;
	int				width;
	int				height;
}	t_texture;

typedef struct s_map
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f_color;
	int		c_color;
	char	**grid;
	int		size;
    int     width;
    int     height;
	int		max_cols;
	int		max_rows;
}	t_map;

typedef struct s_mlx
{
	mlx_t			*mlx;
	mlx_image_t		*img;
}	t_mlx;

typedef struct s_cub
{
	t_map		map;
	t_player	player;
	t_mlx		mlx;
	t_texture	wall_tex;
	t_texture	space_tex;
	t_texture	player_tex;
}	t_cub;

/* Function declarations */

/* Error handling */
void	error_msg(char *msg);
int		err_w_code(char *msg, int exit_code);

/* Input validations */
char	*ft_readline(int fd, int *eof);
int		ft_2d_len(char **arr);
void	ft_clean_arr(char ***arr);
int		get_color(char **rgb_colors, int *ceil_or_floor);
int		all_white_spaces(char *str);

/* Map parsing */
int		path_check(char *path);
int		read_map(int fd, t_cub *cub);
int		read_element(t_map *map, char *line);
int		read_grid(t_map *map, char *line);
int		grid_validation(t_cub *cub, int fd);
bool	is_closed_map(t_map *map, t_dpoint pos);

/* Map utilities */
int		comma_count(char *str);
bool	dir_ele_done(t_map *map);
void	map_cleanup(t_map *map);
int		map_err(t_map *map, char *line, int fd);
int		validate_png(char *path);

/* Graphics functions */
int		init_mlx(t_cub *cub);
int		load_textures(t_cub *cub);
void	cleanup_textures(t_cub *cub);
void	cleanup_mlx(t_cub *cub);
int		render_frame(t_cub *cub);
int		expose_hook(t_cub *cub);
void	draw_texture_to_screen(t_cub *cub, t_texture *tex, int x, int y, int width, int height);

/* Main functions */
int		parse_cub_file(char *filename, t_cub *cub);
void	cleanup_cub(t_cub *cub);

#endif