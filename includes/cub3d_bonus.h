/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:57:55 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/10/17 13:37:43 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "libft.h"
# include <MLX42/MLX42.h>
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/* Constants */
# define G_BUFFER 1024
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_ERROR -1

/* Window settings */
# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 800
# define FOV 60.0
# define PI 3.14159265359
# define CELL_PX 32
# define MINI_TILE 16
# define MINI_TILES_PER_SIDE 10 //check agian
# define M_WIDTH 200
# define M_HEIGHT 200
# define MOVE_SPEED 0.5
# define ROTATE_SPEED 2

# define PLAYER "./assets/textures/player.png"

/* Map characters */
# define PLAYER_N 'N'
# define PLAYER_S 'S'
# define PLAYER_E 'E'
# define PLAYER_W 'W'

/* Element types */
typedef enum e_ele_type
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
}					t_ele_type;

/* Data structures */
typedef struct s_dpoint
{
	double			x;
	double			y;
}					t_dpoint;

typedef struct s_player
{
	t_dpoint		cur_pos;
	t_dpoint		prev_pos;
	double			angle;
	int				found;

}					t_player;

typedef struct s_texture
{
	mlx_texture_t	*tex;
	int				width;
	int				height;
}					t_texture;

typedef struct s_map
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				f_color;
	int				c_color;
	char			**grid;
	int				size;
	int				width;
	int				height;
	int				max_cols;
	int				max_rows;
}					t_map;

typedef struct s_ray
{
	double			angle;
	t_dpoint		hit_pos;
	double			distance;
	int				side;
	double			wall_x;
}					t_ray;

typedef struct s_cub3d_assets
{
	mlx_image_t		*player;
	mlx_image_t		*walls[4];
	mlx_image_t		*ceiling;
	mlx_image_t		*floor;
	mlx_image_t		*map;
	mlx_image_t		*scene;
	mlx_image_t		*minimap_img;
	mlx_image_t		*minimap_bg;
}					t_cub3d_assets;

typedef struct s_cam
{
	double			dirx;
	double			diry;
	double			plx;
	double			ply;

}					t_cam;

typedef struct s_ddaw
{
	double			rdx;
	double			rdy;
	double			ddx;
	double			ddy;
	double			sdx;
	double			sdy;
	int				stepx;
	int				stepy;
	int				mx;
	int				my;
	double			perp;
}					t_ddaw;

typedef struct s_col
{
	int				h;
	int				y0;
	int				y1;
	int				tex_x;
	double			tex_pos_y;
	double			tex_step_y;
	mlx_image_t		*tex;
}					t_col;

typedef struct s_cub
{
	mlx_t			*mlx;
	t_ray			**rays;
	t_map			map;
	t_player		player;
	t_cub3d_assets	assets;
	int32_t			mouse_x;
	int32_t			mouse_y;
	int32_t			prev_mouse_x;
	int32_t			prev_mouse_y;
}					t_cub;

/* Error handling */
void				error_msg(char *msg);
int					err_w_code(char *msg, int exit_code);

/* Input validations */
char				*ft_readline(int fd, int *eof);
int					ft_2d_len(char **arr);
void				ft_clean_arr(char ***arr);
int					get_color(char **rgb_colors, int *ceil_or_floor);
int					all_white_spaces(char *str);

/* Map parsing */
int					path_check(char *path);
int					read_map(int fd, t_cub *cub);
int					read_element(t_map *map, char *line);
int					read_grid(t_map *map, char *line);
int					grid_validation(t_cub *cub, int fd);
bool				is_closed_map(t_map *map, t_dpoint pos);

/* Map utilities */
int					comma_count(char *str);
bool				dir_ele_done(t_map *map);
void				map_cleanup(t_map *map);
int					map_err(t_map *map, char *line, int fd);
int					validate_png(char *path);

/* Function declarations Excute */
void				render_full_map(t_cub *cub);
void				update_minimap_viewport(t_cub *cub);
void				draw_player_dot(t_cub *cub, int xy[2], int wh[2]);

void				draw_wall_column(t_cub *cub, int x, t_col *c);
void				cast_rays(t_cub *cub);
void				dda_init(t_cub *cub, t_cam *cam, int x, t_ddaw *w);
void				dda_run(t_cub *cub, t_ddaw *w, int *out_side);
void				draw_column_and_store(t_cub *cub, int x, t_ddaw *w,
						int side);

mlx_image_t			*new_image(t_cub *cub, uint32_t w, uint32_t h);
void				fill_image(mlx_image_t *img, uint32_t color);
uint32_t			pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
uint32_t			get_tex_color(mlx_image_t *img, int tex_x, int tex_y);

void				load_textures(t_cub *cub);
void				cub3d_init_assets(t_cub *cub);

double				norm_angle(double a);
int					is_wall(const t_map *map, int x, int y);
void				mouse_update(t_cub *cub);
int					rotate_and_escape(t_cub *cub);
void				handle_input(t_cub *cub);

void				cub3d_init(t_cub *cub);
void				cub3d_frame_display(t_cub *cub);

void				cub3d_cleanup(t_cub *cub);
void				cub3d_error_clean(t_cub *cub, const char *msg);

#endif
