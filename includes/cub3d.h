/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:57:55 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/09/29 11:40:05 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42/MLX42.h>
# include "libft.h"
# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <ctype.h>
# include <float.h>
# include <math.h> 
# include <unistd.h> 
# include <errno.h>

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
# define MINI_TILES_PER_SIDE 10
#define M_WIDTH  200
#define M_HEIGHT 200
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
}    t_ele_type;

/* Data structures */
typedef struct s_dpoint
{
    double    x;
    double    y;
}    t_dpoint;

typedef struct s_player
{
    t_dpoint    cur_pos;
    t_dpoint    prev_pos;
    double      angle;
    int    found;   // H—> add

}    t_player;

typedef struct s_texture
{
    mlx_texture_t    *tex;
    int              width;
    int              height;
}    t_texture;

typedef struct s_map
{
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    int     f_color;
    int     c_color;
    char    **grid;
    int     size;
    int     width;
    int     height;
    int     max_cols;
    int     max_rows;
}    t_map;

typedef struct s_ray
{
	double      angle;      
	t_dpoint    hit_pos;    
	double      distance;   
	int         side;       
	double      wall_x;     
} t_ray;

typedef struct s_cub3d_assets
{
    mlx_image_t *player;
    mlx_image_t *walls[4];
    mlx_image_t *ceiling;
    mlx_image_t *floor;
    mlx_image_t *map;
    mlx_image_t *scene;
    mlx_image_t *minimap_img;
    mlx_image_t *minimap_bg;
} t_cub3d_assets;

// map = full map buffer (not directly shown).

// minimap_img = cropped/scaled portion shown in HUD.(head up display)

// minimap_bg = background frame for the minimap.


/////
typedef struct s_cam
{
	double dirx; /* player dir */
    double diry; /* player dir */
	double plx;  /* camera plane from FOV */
    double ply;  /* camera plane from FOV */

} t_cam;

typedef struct s_ddaw
{
	double rdx;  /* ray dir x */
	double rdy;  /* ray dir y */
	double ddx;  /* deltaDist x (|1/rdx|) */
	double ddy;  /* deltaDist y (|1/rdy|) */
	double sdx;  /* sideDist x  */
	double sdy;  /* sideDist y */
	int    stepx;
	int    stepy;
	int    mx;   /* current map cell x */
	int    my;   /* current map cell y */
	double perp; /* perpendicular distance */
} t_ddaw;

typedef struct s_col
{
    int         h;        //wall height in screen pixels
    int         y0;       // top y of the wall slice (clamped to 0)
    int         y1;       // bottom y of the wall slice (clamped to WINDOW_HEIGHT-1)

    int         tex_x;    // x coordinate in the wall texture (column to sample)
    double      tex_pos_y;  // current y position inside the texture (advances per pixel)
    double      tex_step_y; // how much tex_pos_y increases per screen pixel (tex->height / h)

    mlx_image_t *tex;     // texture image to sample for this wall slice
} t_col;

///

/* Root cub */
typedef struct s_cub
{
    mlx_t        *mlx;
    t_ray       **rays;
    t_map        map;
    t_player     player;
    t_cub3d_assets assets;
    int32_t      mouse_x;
    int32_t      mouse_y;
    int32_t      prev_mouse_x;
	int32_t prev_mouse_y;
} t_cub;


// NHAT//

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

/* Function declarations Excute */

void	render_full_map(t_cub *cub);
void	update_minimap_viewport(t_cub *cub);
void	draw_player_dot(t_cub *cub, int xy[2], int wh[2]);

void    draw_wall_column(t_cub *cub, int x, t_col *c);
void	cast_rays(t_cub *cub);
void	dda_init(t_cub *cub, t_cam *cam, int x, t_ddaw *w);
void	dda_run(t_cub *cub, t_ddaw *w, int *out_side);
void	draw_column_and_store(t_cub *cub, int x, t_ddaw *w, int side);

mlx_image_t	*new_image(t_cub *cub, uint32_t w, uint32_t h);
void	fill_image(mlx_image_t *img, uint32_t color);
uint32_t	pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
uint32_t	get_tex_color(mlx_image_t *img, int tex_x, int tex_y);

void	load_textures(t_cub *cub);

void	cub3d_init_assets(t_cub *cub);

double	norm_angle(double a);
int	is_wall(t_map *map, double x, double y);
void	mouse_update(t_cub *cub);
int	rotate_and_escape(t_cub *cub);
void	handle_input(t_cub *cub);

void	cub3d_init(t_cub *cub);

void	cub3d_frame_display(t_cub *cub);


void	cub3d_cleanup(t_cub *cub);
void	cub3d_error_clean(t_cub *cub, const char *msg);


/* Function declarations */

/* Main functions */
//int		parse_cub_file(char *filename, t_cub *cub);
// void	cleanup_cub(t_cub *cub);

#endif
