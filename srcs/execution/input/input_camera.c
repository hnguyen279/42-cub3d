/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-huon <thi-huon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 05:42:49 by thi-huon          #+#    #+#             */
/*   Updated: 2025/09/26 05:42:49 by thi-huon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mouse_update(t_cub *cub)
{
	int		cur_x;
	int		cur_y;
	int		delta_x;
	double	sens_per_sec; //radian/pixel/second
	double	dt;

	mlx_get_mouse_pos(cub->mlx, &cur_x, &cur_y);
	delta_x = cur_x - cub->prev_mouse_x;
	sens_per_sec = 0.1;
	dt = cub->mlx->delta_time;
	cub->player.angle += (double)delta_x * sens_per_sec * dt;
	cub->player.angle = norm_angle(cub->player.angle);
	cub->prev_mouse_x = cur_x;
	cub->prev_mouse_y = cur_y;
}

int	rotate_and_escape(t_cub *cub)
{
	double	dt;

	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(cub->mlx);
		return (1);
	}
	dt = cub->mlx->delta_time;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		cub->player.angle -= ROTATE_SPEED * dt; //// ROTATE_SPEED rad/s
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		cub->player.angle += ROTATE_SPEED * dt;
	cub->player.angle = norm_angle(cub->player.angle);
	return (0);
}
