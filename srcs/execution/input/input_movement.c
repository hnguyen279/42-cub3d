/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 05:42:52 by thi-huon          #+#    #+#             */
/*   Updated: 2025/09/26 05:42:52 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	move_ws(t_cub *cub, double step, double dir_x, double dir_y)
// {
// 	double	nx;
// 	double	ny;

// 	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
// 	{
// 		nx = cub->player.cur_pos.x + dir_x * step;
// 		ny = cub->player.cur_pos.y + dir_y * step;
// 		if (!is_wall(&cub->map, nx, cub->player.cur_pos.y))
// 			cub->player.cur_pos.x = nx;
// 		if (!is_wall(&cub->map, cub->player.cur_pos.x, ny))
// 			cub->player.cur_pos.y = ny;
// 	}
// 	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
// 	{
// 		nx = cub->player.cur_pos.x - dir_x * step;
// 		ny = cub->player.cur_pos.y - dir_y * step;
// 		if (!is_wall(&cub->map, nx, cub->player.cur_pos.y))
// 			cub->player.cur_pos.x = nx;
// 		if (!is_wall(&cub->map, cub->player.cur_pos.x, ny))
// 			cub->player.cur_pos.y = ny;
// 	}
// }

// static void	strafe_ad(t_cub *cub, double step, double dir_x, double dir_y)
// {
// 	double	px;
// 	double	py;
// 	double	nx;
// 	double	ny;

// 	px = -dir_y;
// 	py = dir_x;
// 	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
// 	{
// 		nx = cub->player.cur_pos.x + px * step;
// 		ny = cub->player.cur_pos.y + py * step;
// 		if (!is_wall(&cub->map, nx, cub->player.cur_pos.y))
// 			cub->player.cur_pos.x = nx;
// 		if (!is_wall(&cub->map, cub->player.cur_pos.x, ny))
// 			cub->player.cur_pos.y = ny;
// 	}
// 	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
// 	{
// 		nx = cub->player.cur_pos.x - px * step;
// 		ny = cub->player.cur_pos.y - py * step;
// 		if (!is_wall(&cub->map, nx, cub->player.cur_pos.y))
// 			cub->player.cur_pos.x = nx;
// 		if (!is_wall(&cub->map, cub->player.cur_pos.x, ny))
// 			cub->player.cur_pos.y = ny;
// 	}
// }

static int	collides(const t_map *m, double x, double y, double r)
{
	int	gx;
	int	gy;

	gy = (int)floor(y - r);
	while (gy <= (int)floor(y + r))
	{
		gx = (int)floor(x - r);
		while (gx <= (int)floor(x + r))
		{
			if (is_wall((t_map *)m, gx, gy))
				return (1);
			gx++;
		}
		gy++;
	}
	return (0);
}


static void try_move_axis(t_cub *cub, double dx, double dy, int axis)
{
	double r;
	double nx;
	double ny;

	r = 0.15;
	nx = cub->player.cur_pos.x + dx;
	ny = cub->player.cur_pos.y + dy;
	if (axis == 0)
	{
		if (!collides(&cub->map, nx, cub->player.cur_pos.y, r))
			cub->player.cur_pos.x = nx;
	} 
	else 
	{
		if (!collides(&cub->map, cub->player.cur_pos.x, ny, r))
			cub->player.cur_pos.y = ny;
	}
}

static void move_with_radius(t_cub *cub, double step, double dir_x, double dir_y)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
	{
		try_move_axis(cub, dir_x * step, 0.0, 0);
		try_move_axis(cub, 0.0, dir_y * step, 1);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
	{
		try_move_axis(cub, -dir_x * step, 0.0, 0);
		try_move_axis(cub, 0.0, -dir_y * step, 1);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
	{
		try_move_axis(cub, -dir_y * step, 0.0, 0);
		try_move_axis(cub, 0.0, dir_x * step, 1);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
	{
		try_move_axis(cub, dir_y * step, 0.0, 0);
		try_move_axis(cub, 0.0, -dir_x * step, 1);
	}
}

void	handle_input(t_cub *cub)
{
	double	dir_x;
	double	dir_y;
	double	dt;
	double	step;

	mouse_update(cub);
	if (rotate_and_escape(cub))
		return ;
	dir_x = cos(cub->player.angle);
	dir_y = sin(cub->player.angle);
	dt = cub->mlx->delta_time;
	step = MOVE_SPEED * dt;
	// move_ws(cub, step, dir_x, dir_y);
	// strafe_ad(cub, step, dir_x, dir_y);
	move_with_radius(cub, step, dir_x, dir_y);
	cub->player.angle = norm_angle(cub->player.angle);
}
